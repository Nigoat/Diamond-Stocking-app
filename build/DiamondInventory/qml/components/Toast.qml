import QtQuick
import DiamondInventory

Rectangle {
    id: root

    property string message: ""
    property string type: "info"

    visible: opacity > 0
    opacity: 0
    radius: Theme.radiusMedium
    color: {
        switch (type) {
        case "success": return Theme.isDark ? "#064e3b" : "#d1fae5";
        case "error": return Theme.isDark ? "#7f1d1d" : "#fee2e2";
        default: return Theme.isDark ? "#1e293b" : "#f1f5f9";
        }
    }
    border.color: {
        switch (type) {
        case "success": return Theme.success;
        case "error": return Theme.danger;
        default: return Theme.accent;
        }
    }
    border.width: 1

    implicitWidth: Math.min(480, label.implicitWidth + 36)
    implicitHeight: 44

    Behavior on opacity {
        NumberAnimation { duration: 250; easing.type: Easing.OutQuad }
    }

    Behavior on y {
        NumberAnimation { duration: 250; easing.type: Easing.OutQuad }
    }

    Row {
        anchors.centerIn: parent
        spacing: 10

        Rectangle {
            width: 8
            height: 8
            radius: 4
            anchors.verticalCenter: parent.verticalCenter
            color: {
                switch (root.type) {
                case "success": return Theme.success;
                case "error": return Theme.danger;
                default: return Theme.accent;
                }
            }
        }

        Text {
            id: label
            text: root.message
            font.pixelSize: Theme.fontNormal
            font.weight: Font.Medium
            color: {
                switch (root.type) {
                case "success": return Theme.isDark ? "#6ee7b7" : "#065f46";
                case "error": return Theme.isDark ? "#fca5a5" : "#991b1b";
                default: return Theme.textPrimary;
                }
            }
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Timer {
        id: hideTimer
        interval: 3500
        repeat: false
        onTriggered: {
            root.opacity = 0
        }
    }

    function show(msgType, text) {
        root.type = msgType
        root.message = text
        root.opacity = 1
        hideTimer.restart()
    }
}
