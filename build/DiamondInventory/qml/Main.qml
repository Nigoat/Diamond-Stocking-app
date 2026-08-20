import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import DiamondInventory

Window {
    id: mainWindow

    width: 1280
    height: 800
    minimumWidth: 900
    minimumHeight: 600
    visible: true
    title: AppController.appName + " — " + Settings.storeName

    color: Theme.bgPrimary

    Component.onCompleted: {
        var w = AppController.settings.getUiSetting("windowWidth", 1280)
        var h = AppController.settings.getUiSetting("windowHeight", 800)
        if (w > 0 && h > 0) {
            mainWindow.width = w
            mainWindow.height = h
        }
        if (AppController.settings.getUiSetting("windowMaximized", false)) {
            mainWindow.showMaximized()
        }
    }

    onClosing: {
        AppController.settings.setUiSetting("windowWidth", mainWindow.width)
        AppController.settings.setUiSetting("windowHeight", mainWindow.height)
        AppController.settings.setUiSetting("windowMaximized", mainWindow.visibility === Window.Maximized)
    }

    Connections {
        target: AppController
        function onToastRequested(type, message) {
            globalToast.show(type, message)
        }
    }

    Shortcut {
        sequence: "Ctrl+F"
        onActivated: {
            sidebar.currentPage = 1
            pageStack.currentIndex = 1
            inventoryPage.searchFocus()
        }
    }

    Shortcut {
        sequence: "Ctrl+N"
        onActivated: {
            sidebar.currentPage = 1
            pageStack.currentIndex = 1
            inventoryPage.addNew()
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        AppSidebar {
            id: sidebar
            Layout.preferredWidth: 200
            Layout.fillHeight: true
            onPageChanged: (page) => {
                pageStack.currentIndex = page
            }
        }

        StackLayout {
            id: pageStack
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: 0

            onCurrentIndexChanged: {
                if (currentIndex === 0) dashboardPage.refresh()
                if (currentIndex === 3) reportsPage.refresh()
            }

            DashboardPage {
                id: dashboardPage
            }

            Rectangle {
                id: inventoryWrapper
                color: Theme.bgPrimary

                property bool showingDetails: false
                property int detailDiamondId: 0

                InventoryPage {
                    id: inventoryPage
                    anchors.fill: parent
                    visible: !parent.showingDetails

                    onOpenDiamondDetails: (id) => {
                        parent.detailDiamondId = id
                        parent.showingDetails = true
                        detailsPage.diamondId = id
                        detailsPage.reload()
                    }

                    function searchFocus() {}
                    function addNew() {}
                }

                DiamondDetailsPage {
                    id: detailsPage
                    anchors.fill: parent
                    visible: parent.showingDetails

                    onGoBack: {
                        parent.showingDetails = false
                        DiamondModel.reload()
                    }
                }
            }

            SuppliersPage {
                id: suppliersPage
            }

            ReportsPage {
                id: reportsPage
            }

            SettingsPage {
                id: settingsPage
            }
        }
    }

    Toast {
        id: globalToast
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 32
        z: 9999
    }
}
