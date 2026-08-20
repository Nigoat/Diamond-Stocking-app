import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import DiamondInventory

Rectangle {
    id: root
    color: Theme.bgPrimary

    Flickable {
        anchors.fill: parent
        anchors.margins: 24
        contentHeight: settingsCol.implicitHeight + 32
        clip: true

        ColumnLayout {
            id: settingsCol
            width: parent.width
            spacing: 24

            Text {
                text: "Settings"
                font.pixelSize: Theme.fontTitle
                font.weight: Font.Bold
                color: Theme.textPrimary
            }

            Rectangle {
                Layout.fillWidth: true
                height: storeSection.implicitHeight + 32
                radius: Theme.radiusLarge
                color: Theme.bgCard
                border.color: Theme.border
                border.width: 1

                ColumnLayout {
                    id: storeSection
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 16

                    Text { text: "Store Information"; font.pixelSize: Theme.fontLarge; font.weight: Font.Bold; color: Theme.textPrimary }
                    Rectangle { Layout.fillWidth: true; height: 1; color: Theme.border }

                    GridLayout {
                        Layout.fillWidth: true
                        columns: 2
                        rowSpacing: 12
                        columnSpacing: 14

                        ColumnLayout {
                            spacing: 4
                            Text { text: "Store Name"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                            TextField {
                                id: storeNameField
                                Layout.fillWidth: true
                                color: Theme.textPrimary
                                font.pixelSize: Theme.fontNormal
                                text: Settings.storeName
                                onEditingFinished: Settings.storeName = text
                            }
                        }

                        ColumnLayout {
                            spacing: 4
                            Text { text: "Phone"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                            TextField {
                                id: phoneField
                                Layout.fillWidth: true
                                color: Theme.textPrimary
                                font.pixelSize: Theme.fontNormal
                                text: Settings.storePhone
                                onEditingFinished: Settings.storePhone = text
                            }
                        }

                        ColumnLayout {
                            spacing: 4
                            Text { text: "Email"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                            TextField {
                                id: emailField
                                Layout.fillWidth: true
                                color: Theme.textPrimary
                                font.pixelSize: Theme.fontNormal
                                text: Settings.storeEmail
                                onEditingFinished: Settings.storeEmail = text
                            }
                        }

                        ColumnLayout {
                            Layout.columnSpan: 2
                            spacing: 4
                            Text { text: "Address"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                            TextField {
                                id: addressField
                                Layout.fillWidth: true
                                color: Theme.textPrimary
                                font.pixelSize: Theme.fontNormal
                                text: Settings.storeAddress
                                onEditingFinished: Settings.storeAddress = text
                            }
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: appearanceSection.implicitHeight + 32
                radius: Theme.radiusLarge
                color: Theme.bgCard
                border.color: Theme.border
                border.width: 1

                ColumnLayout {
                    id: appearanceSection
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 16

                    Text { text: "Appearance"; font.pixelSize: Theme.fontLarge; font.weight: Font.Bold; color: Theme.textPrimary }
                    Rectangle { Layout.fillWidth: true; height: 1; color: Theme.border }

                    RowLayout {
                        spacing: 20

                        Text { text: "Theme:"; font.pixelSize: Theme.fontNormal; color: Theme.textSecondary }

                        Repeater {
                            model: ["Light", "Dark", "System"]

                            Rectangle {
                                width: 90
                                height: 36
                                radius: Theme.radiusMedium
                                color: Settings.theme === modelData ? Theme.accentLight : Theme.bgInput
                                border.color: Settings.theme === modelData ? Theme.accent : Theme.border
                                border.width: 1

                                Text {
                                    anchors.centerIn: parent
                                    text: modelData
                                    font.pixelSize: Theme.fontNormal
                                    font.weight: Settings.theme === modelData ? Font.DemiBold : Font.Normal
                                    color: Settings.theme === modelData ? Theme.accent : Theme.textSecondary
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: Settings.theme = modelData
                                }
                            }
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: backupSection.implicitHeight + 32
                radius: Theme.radiusLarge
                color: Theme.bgCard
                border.color: Theme.border
                border.width: 1

                ColumnLayout {
                    id: backupSection
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 16

                    Text { text: "Backup & Restore"; font.pixelSize: Theme.fontLarge; font.weight: Font.Bold; color: Theme.textPrimary }
                    Rectangle { Layout.fillWidth: true; height: 1; color: Theme.border }

                    Text {
                        text: "Last Backup: " + (Settings.lastBackupDate.length > 0 ? Settings.lastBackupDate : "Never")
                        font.pixelSize: Theme.fontNormal
                        color: Theme.textSecondary
                    }

                    RowLayout {
                        spacing: 12

                        Text { text: "Auto Backup:"; font.pixelSize: Theme.fontNormal; color: Theme.textSecondary }
                        ComboBox {
                            id: backupIntervalCombo
                            model: ["daily", "weekly", "always_on_close", "disabled"]
                            currentIndex: {
                                var idx = model.indexOf(Settings.autoBackupInterval)
                                return idx >= 0 ? idx : 0
                            }
                            onCurrentTextChanged: Settings.autoBackupInterval = currentText
                        }
                    }

                    RowLayout {
                        spacing: 12

                        Button {
                            text: "💾 Backup Now"
                            highlighted: true
                            onClicked: AppController.createBackup()
                        }

                        Button {
                            text: "📂 Open Backups Folder"
                            onClicked: AppController.openBackupsFolder()
                        }

                        Button {
                            text: "Load Demo Data"
                            onClicked: {
                                AppController.seedDemoData()
                            }
                        }
                    }

                    Text { text: "Saved Backups:"; font.pixelSize: Theme.fontMedium; font.weight: Font.Bold; color: Theme.textPrimary }

                    ListView {
                        id: backupList
                        Layout.fillWidth: true
                        Layout.preferredHeight: Math.max(60, Math.min(300, count * 52))
                        model: AppController.listBackups()
                        interactive: false
                        clip: true

                        delegate: Rectangle {
                            width: backupList.width
                            height: 48
                            color: "transparent"

                            Rectangle {
                                anchors.bottom: parent.bottom
                                width: parent.width
                                height: 1
                                color: Theme.border
                            }

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 8
                                spacing: 12

                                Column {
                                    spacing: 2
                                    Layout.fillWidth: true

                                    Text {
                                        text: modelData.fileName || ""
                                        font.pixelSize: Theme.fontNormal
                                        font.weight: Font.DemiBold
                                        color: Theme.textPrimary
                                    }

                                    Row {
                                        spacing: 10
                                        Text {
                                            text: modelData.dateFormatted || ""
                                            font.pixelSize: Theme.fontSmall
                                            color: Theme.textMuted
                                        }
                                        Text {
                                            text: "•"
                                            color: Theme.textMuted
                                        }
                                        Text {
                                            text: modelData.sizeFormatted || ""
                                            font.pixelSize: Theme.fontSmall
                                            color: Theme.textMuted
                                        }
                                        Text {
                                            text: "•"
                                            color: Theme.textMuted
                                        }
                                        Text {
                                            text: (modelData.diamondCount || 0) + " diamonds"
                                            font.pixelSize: Theme.fontSmall
                                            color: Theme.textMuted
                                        }
                                    }
                                }

                                Button {
                                    text: "Restore"
                                    onClicked: {
                                        restoreConfirm.backupPath = modelData.fullPath
                                        restoreConfirm.open()
                                    }
                                }
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "No backups found."
                            font.pixelSize: Theme.fontNormal
                            color: Theme.textMuted
                            visible: backupList.count === 0
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: aboutSection.implicitHeight + 32
                radius: Theme.radiusLarge
                color: Theme.bgCard
                border.color: Theme.border
                border.width: 1

                ColumnLayout {
                    id: aboutSection
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 12

                    Text { text: "About"; font.pixelSize: Theme.fontLarge; font.weight: Font.Bold; color: Theme.textPrimary }
                    Rectangle { Layout.fillWidth: true; height: 1; color: Theme.border }

                    Text { text: AppController.appName; font.pixelSize: Theme.fontHeading; font.weight: Font.Bold; color: Theme.textPrimary }
                    Text { text: "Version " + AppController.appVersion; font.pixelSize: Theme.fontNormal; color: Theme.textSecondary }
                    Text { text: "Professional diamond inventory management."; font.pixelSize: Theme.fontNormal; color: Theme.textMuted }
                    Text { text: "Database: SQLite   Framework: Qt 6   License: MIT"; font.pixelSize: Theme.fontSmall; color: Theme.textMuted }
                }
            }

            Item { height: 16 }
        }
    }

    ConfirmDialog {
        id: restoreConfirm
        property string backupPath: ""
        titleText: "Restore Backup"
        messageText: "This will replace the current database with the selected backup. A safety backup of the current data will be created first."
        confirmButtonText: "Restore"
        isDestructive: true
        onConfirmed: {
            AppController.restoreBackup(restoreConfirm.backupPath)
        }
    }
}
