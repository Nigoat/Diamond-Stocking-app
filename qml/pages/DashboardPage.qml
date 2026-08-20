import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import DiamondInventory

Rectangle {
    id: root

    property var stats: ({})

    color: Theme.bgPrimary
    clip: true

    Flickable {
        anchors.fill: parent
        anchors.margins: 24
        contentHeight: contentColumn.implicitHeight
        clip: true

        Column {
            id: contentColumn
            width: parent.width
            spacing: 24

            Row {
                width: parent.width

                Text {
                    text: "Dashboard"
                    font.pixelSize: Theme.fontTitle
                    font.weight: Font.Bold
                    color: Theme.textPrimary
                }

                Item { width: 1; height: 1; Layout.fillWidth: true }
            }

            GridLayout {
                width: parent.width
                columns: Math.max(2, Math.floor(parent.width / 220))
                rowSpacing: 16
                columnSpacing: 16

                StatCard {
                    title: "Total Diamonds"
                    value: stats.totalCount ? stats.totalCount.toString() : "0"
                    accentColor: Theme.accent
                }

                StatCard {
                    title: "Available"
                    value: stats.availableCount ? stats.availableCount.toString() : "0"
                    accentColor: Theme.success
                }

                StatCard {
                    title: "Reserved"
                    value: stats.reservedCount ? stats.reservedCount.toString() : "0"
                    accentColor: Theme.warning
                }

                StatCard {
                    title: "Sold"
                    value: stats.soldCount ? stats.soldCount.toString() : "0"
                    accentColor: Theme.info
                }

                StatCard {
                    title: "Purchase Cost"
                    value: stats.totalPurchaseCostFormatted || "0 MAD"
                    subtitle: "Available stock"
                    accentColor: Theme.textSecondary
                }

                StatCard {
                    title: "Potential Selling Value"
                    value: stats.totalSellingValueFormatted || "0 MAD"
                    subtitle: "Available stock"
                    accentColor: Theme.success
                }

                StatCard {
                    title: "Potential Margin"
                    value: stats.potentialMarginFormatted || "0 MAD"
                    subtitle: stats.potentialMarginPercentage ? Number(stats.potentialMarginPercentage).toFixed(1) + "% avg margin" : ""
                    accentColor: Theme.accent
                }

                StatCard {
                    title: "Missing Images"
                    value: stats.missingImagesCount ? stats.missingImagesCount.toString() : "0"
                    subtitle: "Diamonds without photos"
                    accentColor: Theme.warning
                }
            }

            Column {
                width: parent.width
                spacing: 12

                Text {
                    text: "Recently Added"
                    font.pixelSize: Theme.fontLarge
                    font.weight: Font.Bold
                    color: Theme.textPrimary
                }

                Rectangle {
                    width: parent.width
                    height: recentList.count > 0 ? recentList.contentHeight + 2 : 60
                    radius: Theme.radiusLarge
                    color: Theme.bgCard
                    border.color: Theme.border
                    border.width: 1
                    clip: true

                    ListView {
                        id: recentList
                        anchors.fill: parent
                        model: stats.recentlyAdded || []
                        interactive: false

                        delegate: Rectangle {
                            width: recentList.width
                            height: 48
                            color: "transparent"

                            Rectangle {
                                anchors.bottom: parent.bottom
                                width: parent.width
                                height: 1
                                color: Theme.border
                                visible: index < recentList.count - 1
                            }

                            Row {
                                anchors.fill: parent
                                anchors.margins: 14
                                spacing: 14

                                Rectangle {
                                    width: 32
                                    height: 32
                                    radius: Theme.radiusSmall
                                    color: Theme.bgInput
                                    clip: true
                                    anchors.verticalCenter: parent.verticalCenter

                                    Image {
                                        anchors.fill: parent
                                        source: modelData.mainImageThumbnail ? ("file://" + modelData.mainImageThumbnail) : ""
                                        fillMode: Image.PreserveAspectCrop
                                        asynchronous: true
                                        visible: source.toString().length > 0 && status === Image.Ready
                                    }

                                    Text {
                                        anchors.centerIn: parent
                                        text: "💎"
                                        font.pixelSize: 14
                                        opacity: 0.4
                                        visible: !modelData.mainImageThumbnail
                                    }
                                }

                                Column {
                                    spacing: 2
                                    anchors.verticalCenter: parent.verticalCenter
                                    width: parent.width - 200

                                    Text {
                                        text: modelData.reference || ""
                                        font.pixelSize: Theme.fontNormal
                                        font.weight: Font.Bold
                                        color: Theme.accent
                                    }

                                    Text {
                                        text: modelData.name || ""
                                        font.pixelSize: Theme.fontSmall
                                        color: Theme.textSecondary
                                        elide: Text.ElideRight
                                        width: parent.width
                                    }
                                }

                                Item { width: 1; height: 1 }

                                Text {
                                    text: modelData.sellingPriceFormatted || ""
                                    font.pixelSize: Theme.fontNormal
                                    font.weight: Font.Bold
                                    color: Theme.textPrimary
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                StatusBadge {
                                    status: modelData.status || "Available"
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "No diamonds added yet."
                            font.pixelSize: Theme.fontNormal
                            color: Theme.textMuted
                            visible: recentList.count === 0
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        root.stats = AppController.getDashboardStats()
    }

    function refresh() {
        root.stats = AppController.getDashboardStats()
    }
}
