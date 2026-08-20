import QtQuick
import QtQuick.Controls.Basic
import DiamondInventory

Rectangle {
    id: root

    property alias text: input.text
    property alias placeholderText: input.placeholderText
    signal textModified(string newText)

    implicitWidth: 320
    implicitHeight: 38
    radius: Theme.radiusMedium
    color: Theme.bgInput
    border.color: input.activeFocus ? Theme.borderFocus : Theme.border
    border.width: 1

    Behavior on border.color {
        ColorAnimation { duration: 150 }
    }

    Row {
        anchors.fill: parent
        anchors.leftMargin: 12
        anchors.rightMargin: 8
        spacing: 8

        Text {
            text: "🔍"
            font.pixelSize: 14
            color: Theme.textMuted
            anchors.verticalCenter: parent.verticalCenter
        }

        TextField {
            id: input
            width: parent.width - 64
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            placeholderText: "Search diamonds (ref, name, cert, notes)..."
            placeholderTextColor: Theme.textMuted
            color: Theme.textPrimary
            font.pixelSize: Theme.fontNormal
            background: null
            selectByMouse: true

            onTextChanged: {
                debounceTimer.restart()
            }
        }

        Rectangle {
            width: 20
            height: 20
            radius: 10
            color: Theme.bgHover
            visible: input.text.length > 0
            anchors.verticalCenter: parent.verticalCenter

            Text {
                text: "✕"
                font.pixelSize: 10
                color: Theme.textSecondary
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    input.text = ""
                    root.textModified("")
                }
            }
        }
    }

    Timer {
        id: debounceTimer
        interval: 200
        repeat: false
        onTriggered: {
            root.textModified(input.text)
        }
    }

    function forceFocus() {
        input.forceActiveFocus()
        input.selectAll()
    }
}
