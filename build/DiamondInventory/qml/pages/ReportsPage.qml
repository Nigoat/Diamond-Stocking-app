import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import DiamondInventory

Rectangle {
    id: root
    color: Theme.bgPrimary

    property var breakdown: ({})

    Flickable {
        anchors.fill: parent
        anchors.margins: 24
        contentHeight: mainCol.implicitHeight + 32
        clip: true

        ColumnLayout {
            id: mainCol
            width: parent.width
            spacing: 20

            Text {
                text: "Inventory Reports"
                font.pixelSize: Theme.fontTitle
                font.weight: Font.Bold
                color: Theme.textPrimary
            }

            GridLayout {
                Layout.fillWidth: true
                columns: 2
                rowSpacing: 16
                columnSpacing: 16

                Repeater {
                    model: [
                        { title: "Diamonds by Shape", key: "byShape" },
                        { title: "Diamonds by Color", key: "byColor" },
                        { title: "Diamonds by Clarity", key: "byClarity" },
                        { title: "Diamonds by Status", key: "byStatus" },
                        { title: "Diamonds by Supplier", key: "bySupplier" }
                    ]

                    Rectangle {
                        Layout.fillWidth: true
                        height: sectionCol.implicitHeight + 24
                        radius: Theme.radiusLarge
                        color: Theme.bgCard
                        border.color: Theme.border
                        border.width: 1

                        ColumnLayout {
                            id: sectionCol
                            anchors.fill: parent
                            anchors.margins: 16
                            spacing: 10

                            Text {
                                text: modelData.title
                                font.pixelSize: Theme.fontMedium
                                font.weight: Font.Bold
                                color: Theme.textPrimary
                            }

                            Rectangle { Layout.fillWidth: true; height: 1; color: Theme.border }

                            Repeater {
                                model: root.breakdown[modelData.key] || []

                                RowLayout {
                                    Layout.fillWidth: true

                                    Text {
                                        text: modelData.label || "-"
                                        font.pixelSize: Theme.fontNormal
                                        color: Theme.textSecondary
                                        Layout.preferredWidth: 120
                                    }

                                    Rectangle {
                                        Layout.fillWidth: true
                                        height: 12
                                        radius: 6
                                        color: Theme.bgInput

                                        property real maxCount: {
                                            var arr = root.breakdown[parent.parent.parent.parent.objectName] || []
                                            var max = 1
                                            for (var i = 0; i < arr.length; ++i) {
                                                if (arr[i].count > max) max = arr[i].count
                                            }
                                            return max
                                        }

                                        Rectangle {
                                            width: parent.width * Math.min(1, modelData.count / Math.max(1, parent.maxCount))
                                            height: parent.height
                                            radius: 6
                                            color: Theme.accent
                                            Behavior on width { NumberAnimation { duration: 400; easing.type: Easing.OutQuad } }
                                        }
                                    }

                                    Text {
                                        text: modelData.count + " (" + modelData.totalValueFormatted + ")"
                                        font.pixelSize: Theme.fontSmall
                                        color: Theme.textMuted
                                        Layout.preferredWidth: 150
                                        horizontalAlignment: Text.AlignRight
                                    }
                                }
                            }

                            Text {
                                text: "No data available."
                                font.pixelSize: Theme.fontNormal
                                color: Theme.textMuted
                                visible: !root.breakdown[modelData.key] || root.breakdown[modelData.key].length === 0
                            }
                        }
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 12

                Button {
                    text: "⤓ Export CSV"
                    onClicked: AppController.exportCsv("")
                }

                Button {
                    text: "⤓ Export PDF"
                    onClicked: AppController.exportPdf("")
                }

                Button {
                    text: "Open Exports Folder"
                    onClicked: AppController.openExportsFolder()
                }
            }

            Item { height: 16 }
        }
    }

    Component.onCompleted: {
        root.breakdown = AppController.getReportsBreakdown()
    }

    function refresh() {
        root.breakdown = AppController.getReportsBreakdown()
    }
}
