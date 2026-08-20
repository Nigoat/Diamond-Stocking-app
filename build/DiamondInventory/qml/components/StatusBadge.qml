import QtQuick
import DiamondInventory

Rectangle {
    id: root

    property string status: "Available"
    property int fontSize: Theme.fontSmall

    implicitWidth: rowLayout.implicitWidth + 16
    implicitHeight: 24
    radius: Theme.radiusFull
    color: Theme.statusBgColor(status)
    border.color: Qt.alpha(Theme.statusColor(status), 0.3)
    border.width: 1

    Row {
        id: rowLayout
        anchors.centerIn: parent
        spacing: 6

        Rectangle {
            width: 7
            height: 7
            radius: 4
            anchors.verticalCenter: parent.verticalCenter
            color: Theme.statusColor(root.status)
        }

        Text {
            text: root.status
            font.pixelSize: root.fontSize
            font.weight: Font.DemiBold
            color: Theme.statusTextColor(root.status)
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
