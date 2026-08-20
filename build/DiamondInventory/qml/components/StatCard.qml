import QtQuick
import DiamondInventory

Rectangle {
    id: root

    property string title: ""
    property string value: "0"
    property string subtitle: ""
    property color accentColor: Theme.accent

    implicitWidth: 220
    implicitHeight: 110
    radius: Theme.radiusLarge
    color: Theme.bgCard
    border.color: Theme.border
    border.width: 1

    Column {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 6

        Row {
            width: parent.width
            spacing: 8

            Rectangle {
                width: 4
                height: 14
                radius: 2
                color: root.accentColor
                anchors.verticalCenter: parent.verticalCenter
            }

            Text {
                text: root.title
                font.pixelSize: Theme.fontSmall
                font.weight: Font.DemiBold
                color: Theme.textSecondary
                elide: Text.ElideRight
                width: parent.width - 20
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Text {
            text: root.value
            font.pixelSize: Theme.fontTitle
            font.weight: Font.Bold
            color: Theme.textPrimary
            elide: Text.ElideRight
            width: parent.width
        }

        Text {
            text: root.subtitle
            font.pixelSize: Theme.fontSmall
            color: Theme.textMuted
            visible: text.length > 0
            elide: Text.ElideRight
            width: parent.width
        }
    }
}
