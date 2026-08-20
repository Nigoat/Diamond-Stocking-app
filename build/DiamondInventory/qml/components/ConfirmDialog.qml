import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import DiamondInventory

Dialog {
    id: root

    property string titleText: "Confirm Action"
    property string messageText: "Are you sure you want to proceed?"
    property string confirmButtonText: "Confirm"
    property string cancelButtonText: "Cancel"
    property bool isDestructive: false

    signal confirmed()
    signal cancelled()

    modal: true
    dim: true
    anchors.centerIn: parent
    implicitWidth: 420
    implicitHeight: 200

    background: Rectangle {
        radius: Theme.radiusLarge
        color: Theme.bgCard
        border.color: Theme.border
        border.width: 1
    }

    contentItem: ColumnLayout {
        spacing: 16

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Rectangle {
                width: 32
                height: 32
                radius: 16
                color: root.isDestructive ? Theme.dangerBg : Theme.infoBg

                Text {
                    anchors.centerIn: parent
                    text: root.isDestructive ? "⚠️" : "ℹ️"
                    font.pixelSize: 14
                }
            }

            Text {
                text: root.titleText
                font.pixelSize: Theme.fontLarge
                font.weight: Font.Bold
                color: Theme.textPrimary
                Layout.fillWidth: true
            }
        }

        Text {
            text: root.messageText
            font.pixelSize: Theme.fontNormal
            color: Theme.textSecondary
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        Item { Layout.fillHeight: true }

        RowLayout {
            Layout.fillWidth: true
            spacing: 12

            Item { Layout.fillWidth: true }

            Button {
                text: root.cancelButtonText
                onClicked: {
                    root.close()
                    root.cancelled()
                }
            }

            Button {
                text: root.confirmButtonText
                highlighted: true
                onClicked: {
                    root.close()
                    root.confirmed()
                }
            }
        }
    }
}
