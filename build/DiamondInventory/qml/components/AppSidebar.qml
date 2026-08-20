import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import DiamondInventory

Rectangle {
    id: root

    property int currentPage: 0
    signal pageChanged(int pageIndex)

    implicitWidth: 200
    color: Theme.bgSecondary
    border.color: Theme.border
    border.width: 0

    Rectangle {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 1
        color: Theme.border
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.fillWidth: true
            height: 72
            color: Theme.bgSecondary

            Column {
                anchors.centerIn: parent
                spacing: 2

                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 8

                    Rectangle {
                        width: 28
                        height: 28
                        radius: 6
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: "#38bdf8" }
                            GradientStop { position: 1.0; color: "#4338ca" }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "◆"
                            font.pixelSize: 14
                            color: "#ffffff"
                        }
                    }

                    Text {
                        text: AppController.appName
                        font.pixelSize: Theme.fontMedium
                        font.weight: Font.Bold
                        color: Theme.textPrimary
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Text {
                    text: Settings.storeName
                    font.pixelSize: Theme.fontSmall
                    color: Theme.textMuted
                    anchors.horizontalCenter: parent.horizontalCenter
                    elide: Text.ElideRight
                    width: root.width - 24
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: Theme.border
        }

        Item { Layout.preferredHeight: 8 }

        Repeater {
            model: [
                { icon: "🏠", label: "Dashboard", page: 0 },
                { icon: "💎", label: "Inventory", page: 1 },
                { icon: "🏪", label: "Suppliers", page: 2 },
                { icon: "📊", label: "Reports", page: 3 },
                { icon: "⚙️", label: "Settings", page: 4 }
            ]

            Rectangle {
                width: root.width - 16
                height: 40
                x: 8
                radius: Theme.radiusMedium
                color: root.currentPage === modelData.page ? Theme.accentLight : (navMouse.containsMouse ? Theme.bgHover : "transparent")

                Behavior on color { ColorAnimation { duration: 120 } }

                Row {
                    anchors.fill: parent
                    anchors.leftMargin: 12
                    spacing: 10

                    Rectangle {
                        width: 3
                        height: 20
                        radius: 2
                        anchors.verticalCenter: parent.verticalCenter
                        color: Theme.accent
                        opacity: root.currentPage === modelData.page ? 1 : 0
                        Behavior on opacity { NumberAnimation { duration: 150 } }
                    }

                    Text {
                        text: modelData.icon
                        font.pixelSize: 15
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        text: modelData.label
                        font.pixelSize: Theme.fontNormal
                        font.weight: root.currentPage === modelData.page ? Font.DemiBold : Font.Normal
                        color: root.currentPage === modelData.page ? Theme.accent : Theme.textSecondary
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                MouseArea {
                    id: navMouse
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        root.currentPage = modelData.page
                        root.pageChanged(modelData.page)
                    }
                }
            }
        }

        Item { Layout.fillHeight: true }

        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: Theme.border
        }

        Text {
            text: "v" + AppController.appVersion
            font.pixelSize: Theme.fontSmall
            color: Theme.textMuted
            padding: 12
            Layout.alignment: Qt.AlignLeft
        }
    }
}
