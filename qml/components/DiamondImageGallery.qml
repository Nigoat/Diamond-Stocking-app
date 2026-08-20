import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import QtQuick.Dialogs
import DiamondInventory

Rectangle {
    id: root

    property int diamondId: 0
    property var imagesList: []
    property int selectedIndex: 0

    signal imagesChanged()

    implicitWidth: 380
    implicitHeight: 440
    radius: Theme.radiusLarge
    color: Theme.bgCard
    border.color: Theme.border
    border.width: 1

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 14
        spacing: 10

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: Theme.radiusMedium
            color: Theme.bgInput
            clip: true

            Image {
                id: mainHero
                anchors.fill: parent
                source: (root.imagesList.length > 0 && root.selectedIndex < root.imagesList.length) ?
                        ("file://" + root.imagesList[root.selectedIndex].filePath) : ""
                fillMode: Image.PreserveAspectFit
                asynchronous: true
                visible: source.toString().length > 0 && status === Image.Ready
            }

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                visible: !mainHero.visible

                Column {
                    anchors.centerIn: parent
                    spacing: 8
                    Text { text: "💎"; font.pixelSize: 48; anchors.horizontalCenter: parent.horizontalCenter; opacity: 0.4 }
                    Text { text: "No Image Available"; font.pixelSize: Theme.fontNormal; color: Theme.textMuted; anchors.horizontalCenter: parent.horizontalCenter }
                }
            }

            Rectangle {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.margins: 8
                height: 22
                width: badgeText.implicitWidth + 12
                radius: Theme.radiusSmall
                color: Qt.alpha(Theme.bgPrimary, 0.8)
                visible: root.imagesList.length > 0 && root.selectedIndex < root.imagesList.length && root.imagesList[root.selectedIndex].imageType === "main"

                Text {
                    id: badgeText
                    anchors.centerIn: parent
                    text: "PRIMARY"
                    font.pixelSize: Theme.fontSmall
                    font.weight: Font.Bold
                    color: Theme.accentText
                }
            }
        }

        ListView {
            id: thumbList
            Layout.fillWidth: true
            Layout.preferredHeight: 64
            orientation: ListView.Horizontal
            spacing: 8
            clip: true
            model: root.imagesList

            delegate: Rectangle {
                width: 64
                height: 64
                radius: Theme.radiusSmall
                color: Theme.bgInput
                border.color: root.selectedIndex === index ? Theme.accent : Theme.border
                border.width: root.selectedIndex === index ? 2 : 1
                clip: true

                Image {
                    anchors.fill: parent
                    source: modelData.thumbnailPath ? ("file://" + modelData.thumbnailPath) : ""
                    fillMode: Image.PreserveAspectCrop
                    asynchronous: true
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        root.selectedIndex = index
                    }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            Button {
                text: "+ Add Photo"
                Layout.fillWidth: true
                onClicked: imageFileDialog.open()
            }

            Button {
                text: "Set Primary"
                enabled: root.imagesList.length > 0 && root.selectedIndex < root.imagesList.length && root.imagesList[root.selectedIndex].imageType !== "main"
                onClicked: {
                    var img = root.imagesList[root.selectedIndex]
                    AppController.setMainDiamondImage(root.diamondId, img.id)
                    root.reload()
                }
            }

            Button {
                text: "Delete"
                enabled: root.imagesList.length > 0 && root.selectedIndex < root.imagesList.length
                onClicked: {
                    var img = root.imagesList[root.selectedIndex]
                    AppController.removeDiamondImage(img.id)
                    if (root.selectedIndex > 0) root.selectedIndex--
                    root.reload()
                }
            }
        }
    }

    FileDialog {
        id: imageFileDialog
        title: "Select Diamond Photo"
        nameFilters: ["Image files (*.jpg *.jpeg *.png *.webp)"]
        onAccepted: {
            if (selectedFile) {
                AppController.addDiamondImage(root.diamondId, selectedFile.toString(), "side")
                root.reload()
            }
        }
    }

    function reload() {
        root.imagesList = AppController.getDiamondImages(root.diamondId)
        root.imagesChanged()
    }

    onDiamondIdChanged: {
        root.selectedIndex = 0
        root.reload()
    }
}
