import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import DiamondInventory

Rectangle {
    id: root

    property int diamondId: 0
    property var diamond: ({})

    signal goBack()

    color: Theme.bgPrimary
    clip: true

    Flickable {
        anchors.fill: parent
        contentHeight: mainCol.implicitHeight + 32
        clip: true

        ColumnLayout {
            id: mainCol
            width: parent.width - 48
            x: 24
            y: 24
            spacing: 20

            RowLayout {
                Layout.fillWidth: true

                Rectangle {
                    width: 90
                    height: 36
                    radius: Theme.radiusSmall
                    color: backMouse.containsMouse ? Theme.bgHover : "transparent"
                    border.color: Theme.border
                    border.width: 1

                    Row {
                        anchors.centerIn: parent
                        spacing: 6
                        Text { text: "←"; font.pixelSize: Theme.fontNormal; color: Theme.textSecondary }
                        Text { text: "Back"; font.pixelSize: Theme.fontNormal; color: Theme.textSecondary }
                    }

                    MouseArea {
                        id: backMouse
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: root.goBack()
                    }
                }

                Item { Layout.fillWidth: true }

                Button {
                    text: "✏ Edit"
                    onClicked: {
                        editModal.openEdit(root.diamond)
                    }
                }

                Button {
                    text: "⎙ Print"
                    onClicked: AppController.printDiamondSheet(root.diamondId, "")
                }

                Button {
                    text: root.diamond.isFavorite ? "★ Unfavorite" : "☆ Favorite"
                    onClicked: {
                        AppController.toggleFavorite(root.diamondId)
                        root.reload()
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 28
                Layout.alignment: Qt.AlignTop

                DiamondImageGallery {
                    id: gallery
                    diamondId: root.diamondId
                    Layout.preferredWidth: 380
                    Layout.alignment: Qt.AlignTop
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignTop
                    spacing: 12

                    Text {
                        text: root.diamond.reference || ""
                        font.pixelSize: Theme.fontTitle
                        font.weight: Font.Bold
                        color: Theme.accent
                    }

                    Text {
                        text: root.diamond.name || ""
                        font.pixelSize: Theme.fontHeading
                        font.weight: Font.Medium
                        color: Theme.textPrimary
                        wrapMode: Text.WordWrap
                        Layout.fillWidth: true
                    }

                    Row {
                        spacing: 12

                        Text {
                            text: root.diamond.carat ? Number(root.diamond.carat).toFixed(2) + " ct" : ""
                            font.pixelSize: Theme.fontLarge
                            font.weight: Font.Bold
                            color: Theme.textPrimary
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        Text {
                            text: "•"
                            color: Theme.textMuted
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        Text {
                            text: (root.diamond.shape || "") + " • " + (root.diamond.color || "") + " / " + (root.diamond.clarity || "") + " • " + (root.diamond.cut || "")
                            font.pixelSize: Theme.fontNormal
                            color: Theme.textSecondary
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        height: 68
                        radius: Theme.radiusMedium
                        color: Theme.accentLight
                        border.color: Qt.alpha(Theme.accent, 0.3)
                        border.width: 1

                        Row {
                            anchors.fill: parent
                            anchors.margins: 14
                            spacing: 24

                            Column {
                                spacing: 2
                                anchors.verticalCenter: parent.verticalCenter
                                Text { text: "Selling Price"; font.pixelSize: Theme.fontSmall; color: Theme.textMuted }
                                Text { text: root.diamond.sellingPriceFormatted || ""; font.pixelSize: Theme.fontLarge; font.weight: Font.Bold; color: Theme.accent }
                            }

                            Rectangle { width: 1; height: 40; color: Qt.alpha(Theme.accent, 0.2); anchors.verticalCenter: parent.verticalCenter }

                            Column {
                                spacing: 2
                                anchors.verticalCenter: parent.verticalCenter
                                Text { text: "Purchase Cost"; font.pixelSize: Theme.fontSmall; color: Theme.textMuted }
                                Text { text: root.diamond.purchaseCostFormatted || ""; font.pixelSize: Theme.fontNormal; color: Theme.textSecondary }
                            }

                            Rectangle { width: 1; height: 40; color: Qt.alpha(Theme.accent, 0.2); anchors.verticalCenter: parent.verticalCenter }

                            Column {
                                spacing: 2
                                anchors.verticalCenter: parent.verticalCenter
                                Text { text: "Margin"; font.pixelSize: Theme.fontSmall; color: Theme.textMuted }
                                Text {
                                    text: (root.diamond.marginFormatted || "") + " (" + (root.diamond.marginPercentage ? Number(root.diamond.marginPercentage).toFixed(1) : "0") + "%)"
                                    font.pixelSize: Theme.fontNormal
                                    color: Theme.success
                                }
                            }
                        }
                    }

                    Row {
                        spacing: 12

                        StatusBadge {
                            status: root.diamond.status || "Available"
                            fontSize: Theme.fontNormal
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        Text {
                            text: (root.diamond.location || "") + (root.diamond.locationDetails ? " — " + root.diamond.locationDetails : "")
                            font.pixelSize: Theme.fontNormal
                            color: Theme.textSecondary
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    Row {
                        spacing: 12
                        visible: root.diamond.certNum && root.diamond.certLab && root.diamond.certLab !== "None"

                        Rectangle {
                            height: 30
                            width: certBadgeRow.implicitWidth + 16
                            radius: Theme.radiusSmall
                            color: Theme.bgInput
                            border.color: Theme.border
                            border.width: 1

                            Row {
                                id: certBadgeRow
                                anchors.centerIn: parent
                                spacing: 8
                                Text { text: root.diamond.certLab || ""; font.pixelSize: Theme.fontSmall; font.weight: Font.Bold; color: Theme.accent }
                                Text { text: root.diamond.certNum || ""; font.pixelSize: Theme.fontSmall; color: Theme.textSecondary }
                            }
                        }
                    }

                    Row {
                        spacing: 8
                        visible: root.diamond.supplierName && root.diamond.supplierName.length > 0

                        Text { text: "Supplier:"; font.pixelSize: Theme.fontSmall; color: Theme.textMuted; anchors.verticalCenter: parent.verticalCenter }
                        Text { text: root.diamond.supplierName || ""; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary; anchors.verticalCenter: parent.verticalCenter }
                    }

                    Row {
                        spacing: 12

                        Button {
                            text: "Mark Available"
                            visible: root.diamond.status !== "Available"
                            onClicked: {
                                AppController.updateDiamondStatus(root.diamondId, "Available")
                                root.reload()
                            }
                        }

                        Button {
                            text: "Mark Reserved"
                            visible: root.diamond.status !== "Reserved"
                            onClicked: {
                                AppController.updateDiamondStatus(root.diamondId, "Reserved")
                                root.reload()
                            }
                        }

                        Button {
                            text: "Mark Sold"
                            visible: root.diamond.status !== "Sold"
                            onClicked: {
                                AppController.updateDiamondStatus(root.diamondId, "Sold")
                                root.reload()
                            }
                        }
                    }
                }
            }

            TabBar {
                id: detailTabBar
                Layout.fillWidth: true

                TabButton { text: "Specifications" }
                TabButton { text: "Certificate" }
                TabButton { text: "Pricing" }
                TabButton { text: "History" }
            }

            Rectangle {
                Layout.fillWidth: true
                height: detailTabContent.implicitHeight + 24
                radius: Theme.radiusMedium
                color: Theme.bgCard
                border.color: Theme.border
                border.width: 1
                clip: true

                StackLayout {
                    id: detailTabContent
                    width: parent.width - 32
                    x: 16
                    y: 16
                    currentIndex: detailTabBar.currentIndex

                    GridLayout {
                        columns: 2
                        rowSpacing: 10
                        columnSpacing: 24
                        Layout.fillWidth: true

                        Repeater {
                            model: [
                                { l: "Shape", v: root.diamond.shape },
                                { l: "Carat Weight", v: root.diamond.carat ? Number(root.diamond.carat).toFixed(2) + " ct" : "-" },
                                { l: "Color Grade", v: root.diamond.color },
                                { l: "Clarity Grade", v: root.diamond.clarity },
                                { l: "Cut Grade", v: root.diamond.cut },
                                { l: "Polish", v: root.diamond.polish },
                                { l: "Symmetry", v: root.diamond.symmetry },
                                { l: "Fluorescence", v: root.diamond.fluorescence },
                                { l: "Table %", v: root.diamond.tablePercentage ? root.diamond.tablePercentage + " %" : "-" },
                                { l: "Depth %", v: root.diamond.depthPercentage ? root.diamond.depthPercentage + " %" : "-" },
                                { l: "Measurements", v: root.diamond.measurements || "-" },
                                { l: "Girdle", v: root.diamond.girdle || "-" },
                                { l: "Culet", v: root.diamond.culet || "-" },
                                { l: "SKU", v: root.diamond.sku || "-" },
                                { l: "Barcode", v: root.diamond.barcode || "-" }
                            ]

                            Row {
                                spacing: 12
                                Layout.fillWidth: true

                                Text {
                                    text: modelData.l + ":"
                                    font.pixelSize: Theme.fontSmall
                                    font.weight: Font.DemiBold
                                    color: Theme.textMuted
                                    width: 120
                                }

                                Text {
                                    text: modelData.v || "-"
                                    font.pixelSize: Theme.fontNormal
                                    color: Theme.textPrimary
                                }
                            }
                        }
                    }

                    ColumnLayout {
                        spacing: 12
                        Layout.fillWidth: true

                        Repeater {
                            model: [
                                { l: "Laboratory", v: root.diamond.certLab },
                                { l: "Certificate Number", v: root.diamond.certNum },
                                { l: "Certificate Date", v: root.diamond.certDate },
                                { l: "Certificate Notes", v: root.diamond.certNotes }
                            ]

                            Row {
                                spacing: 12
                                Layout.fillWidth: true

                                Text {
                                    text: modelData.l + ":"
                                    font.pixelSize: Theme.fontSmall
                                    font.weight: Font.DemiBold
                                    color: Theme.textMuted
                                    width: 150
                                }

                                Text {
                                    text: modelData.v || "-"
                                    font.pixelSize: Theme.fontNormal
                                    color: Theme.textPrimary
                                    wrapMode: Text.WordWrap
                                    Layout.fillWidth: true
                                }
                            }
                        }
                    }

                    ColumnLayout {
                        spacing: 12
                        Layout.fillWidth: true

                        Repeater {
                            model: [
                                { l: "Purchase Cost", v: root.diamond.purchaseCostFormatted },
                                { l: "Selling Price", v: root.diamond.sellingPriceFormatted },
                                { l: "Discount Price", v: root.diamond.discountPriceFormatted },
                                { l: "Min. Selling Price", v: root.diamond.minSellingPriceFormatted },
                                { l: "Margin (MAD)", v: root.diamond.marginFormatted },
                                { l: "Margin %", v: root.diamond.marginPercentage ? Number(root.diamond.marginPercentage).toFixed(2) + " %" : "-" }
                            ]

                            Row {
                                spacing: 12
                                Layout.fillWidth: true

                                Text {
                                    text: modelData.l + ":"
                                    font.pixelSize: Theme.fontSmall
                                    font.weight: Font.DemiBold
                                    color: Theme.textMuted
                                    width: 150
                                }

                                Text {
                                    text: modelData.v || "-"
                                    font.pixelSize: Theme.fontNormal
                                    font.weight: modelData.l === "Selling Price" ? Font.Bold : Font.Normal
                                    color: modelData.l === "Margin (MAD)" ? Theme.success : Theme.textPrimary
                                }
                            }
                        }
                    }

                    ListView {
                        id: auditList
                        Layout.fillWidth: true
                        Layout.preferredHeight: Math.min(300, count * 60 + 20)
                        model: root.diamondId > 0 ? AppController.getDiamondAuditLogs(root.diamondId) : []
                        interactive: false

                        delegate: Rectangle {
                            width: auditList.width
                            height: 52
                            color: "transparent"

                            Rectangle {
                                anchors.bottom: parent.bottom
                                width: parent.width
                                height: 1
                                color: Theme.border
                            }

                            Row {
                                anchors.fill: parent
                                anchors.margins: 8
                                spacing: 12

                                Column {
                                    spacing: 2
                                    anchors.verticalCenter: parent.verticalCenter
                                    width: parent.width

                                    Text {
                                        text: modelData.action || ""
                                        font.pixelSize: Theme.fontNormal
                                        font.weight: Font.DemiBold
                                        color: Theme.textPrimary
                                    }

                                    Row {
                                        spacing: 8
                                        Text {
                                            text: modelData.timestamp || ""
                                            font.pixelSize: Theme.fontSmall
                                            color: Theme.textMuted
                                        }
                                        Text {
                                            text: (modelData.oldValue && modelData.newValue) ? (modelData.oldValue + " → " + modelData.newValue) : ""
                                            font.pixelSize: Theme.fontSmall
                                            color: Theme.textSecondary
                                            visible: text.length > 0
                                        }
                                    }
                                }
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "No history recorded yet."
                            font.pixelSize: Theme.fontNormal
                            color: Theme.textMuted
                            visible: auditList.count === 0
                        }
                    }
                }
            }

            Item { height: 24 }
        }
    }

    AddEditDiamondModal {
        id: editModal
        onClosed: root.reload()
    }

    function reload() {
        var data = DiamondModel.getById(root.diamondId)
        root.diamond = data
    }

    onDiamondIdChanged: {
        root.reload()
    }
}
