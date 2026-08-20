import QtQuick
import QtQuick.Controls.Basic
import DiamondInventory

Rectangle {
    id: root

    property var diamondData: ({})
    signal openDetails(int diamondId)
    signal contextMenuRequested(int diamondId, real mouseX, real mouseY)

    implicitWidth: 260
    implicitHeight: 330
    radius: Theme.radiusLarge
    color: cardMouse.containsMouse ? Theme.bgHover : Theme.bgCard
    border.color: diamondData.selected ? Theme.accent : (cardMouse.containsMouse ? Theme.borderFocus : Theme.border)
    border.width: diamondData.selected ? 2 : 1

    Behavior on color { ColorAnimation { duration: 120 } }
    Behavior on border.color { ColorAnimation { duration: 120 } }

    Column {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 10

        Rectangle {
            width: parent.width
            height: 160
            radius: Theme.radiusMedium
            color: Theme.bgInput
            clip: true

            Image {
                anchors.fill: parent
                source: diamondData.mainThumbnail ? ("file://" + diamondData.mainThumbnail) : ""
                fillMode: Image.PreserveAspectCrop
                asynchronous: true
                visible: source.toString().length > 0 && status === Image.Ready
            }

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                visible: !diamondData.mainThumbnail

                Text {
                    anchors.centerIn: parent
                    text: "💎"
                    font.pixelSize: 42
                    opacity: 0.4
                }
            }

            Rectangle {
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.margins: 8
                width: 28
                height: 28
                radius: 14
                color: Qt.alpha(Theme.bgSecondary, 0.8)

                Text {
                    anchors.centerIn: parent
                    text: diamondData.isFavorite ? "★" : "☆"
                    font.pixelSize: 16
                    color: diamondData.isFavorite ? "#fbbf24" : Theme.textSecondary
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        AppController.toggleFavorite(diamondData.diamondId)
                    }
                }
            }

            Rectangle {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.margins: 8
                height: 22
                width: certText.implicitWidth + 12
                radius: Theme.radiusSmall
                color: Qt.alpha(Theme.bgPrimary, 0.8)
                visible: diamondData.certLab && diamondData.certLab !== "None"

                Text {
                    id: certText
                    anchors.centerIn: parent
                    text: diamondData.certLab
                    font.pixelSize: Theme.fontSmall
                    font.weight: Font.Bold
                    color: Theme.accentText
                }
            }
        }

        Row {
            width: parent.width
            spacing: 8

            Text {
                text: diamondData.reference || ""
                font.pixelSize: Theme.fontNormal
                font.weight: Font.Bold
                color: Theme.accent
                elide: Text.ElideRight
                width: parent.width - statusBadgeItem.implicitWidth - 8
                anchors.verticalCenter: parent.verticalCenter
            }

            StatusBadge {
                id: statusBadgeItem
                status: diamondData.status || "Available"
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Text {
            text: diamondData.name || ""
            font.pixelSize: Theme.fontNormal
            font.weight: Font.Medium
            color: Theme.textPrimary
            elide: Text.ElideRight
            width: parent.width
        }

        Text {
            text: (diamondData.carat ? Number(diamondData.carat).toFixed(2) + " ct" : "") + " • " + (diamondData.shape || "") + " • " + (diamondData.color || "") + " / " + (diamondData.clarity || "")
            font.pixelSize: Theme.fontSmall
            color: Theme.textSecondary
            elide: Text.ElideRight
            width: parent.width
        }

        Item { Layout.fillHeight: true; width: 1; height: 1 }

        Row {
            width: parent.width

            Text {
                text: diamondData.sellingPriceFormatted || ""
                font.pixelSize: Theme.fontLarge
                font.weight: Font.Bold
                color: Theme.textPrimary
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    MouseArea {
        id: cardMouse
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        cursorShape: Qt.PointingHandCursor

        onClicked: (mouse) => {
            if (mouse.button === Qt.RightButton) {
                root.contextMenuRequested(diamondData.diamondId, mouse.x, mouse.y)
            } else {
                root.openDetails(diamondData.diamondId)
            }
        }
    }
}
