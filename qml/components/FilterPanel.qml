import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import DiamondInventory

Rectangle {
    id: root

    property bool isExpanded: false

    implicitWidth: parent ? parent.width : 800
    implicitHeight: isExpanded ? filterContent.implicitHeight + 24 : 0
    visible: isExpanded || height > 0
    clip: true
    radius: Theme.radiusMedium
    color: Theme.bgCard
    border.color: Theme.border
    border.width: 1

    Behavior on implicitHeight {
        NumberAnimation { duration: 200; easing.type: Easing.OutQuad }
    }

    ColumnLayout {
        id: filterContent
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        GridLayout {
            Layout.fillWidth: true
            columns: 4
            rowSpacing: 10
            columnSpacing: 14

            ColumnLayout {
                spacing: 4
                Text { text: "Shape"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                ComboBox {
                    id: shapeCombo
                    Layout.fillWidth: true
                    model: ["All", "Round", "Princess", "Cushion", "Oval", "Emerald", "Radiant", "Pear", "Marquise", "Asscher", "Heart", "Other"]
                    onCurrentTextChanged: DiamondModel.currentShape = currentText
                }
            }

            ColumnLayout {
                spacing: 4
                Text { text: "Status"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                ComboBox {
                    id: statusCombo
                    Layout.fillWidth: true
                    model: ["All", "Available", "Reserved", "Sold", "Unavailable", "Returned"]
                    onCurrentTextChanged: DiamondModel.currentStatus = currentText
                }
            }

            ColumnLayout {
                spacing: 4
                Text { text: "Color Grade"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                ComboBox {
                    id: colorCombo
                    Layout.fillWidth: true
                    model: ["All", "D", "E", "F", "G", "H", "I", "J", "K", "Other"]
                    onCurrentTextChanged: DiamondModel.currentColor = currentText
                }
            }

            ColumnLayout {
                spacing: 4
                Text { text: "Clarity Grade"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                ComboBox {
                    id: clarityCombo
                    Layout.fillWidth: true
                    model: ["All", "FL", "IF", "VVS1", "VVS2", "VS1", "VS2", "SI1", "SI2", "I1", "I2", "I3"]
                    onCurrentTextChanged: DiamondModel.currentClarity = currentText
                }
            }

            ColumnLayout {
                spacing: 4
                Text { text: "Cut Grade"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                ComboBox {
                    id: cutCombo
                    Layout.fillWidth: true
                    model: ["All", "Excellent", "Very Good", "Good", "Fair", "Poor"]
                    onCurrentTextChanged: DiamondModel.currentCut = currentText
                }
            }

            ColumnLayout {
                spacing: 4
                Text { text: "Certificate Lab"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                ComboBox {
                    id: labCombo
                    Layout.fillWidth: true
                    model: ["All", "GIA", "IGI", "HRD", "GCAL", "None"]
                    onCurrentTextChanged: DiamondModel.currentLab = currentText
                }
            }

            ColumnLayout {
                spacing: 4
                Text { text: "Carat Weight (Min - Max)"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 6
                    TextField {
                        id: minCaratInput
                        Layout.fillWidth: true
                        placeholderText: "0.00"
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontNormal
                        onEditingFinished: DiamondModel.minCarat = text.length > 0 ? parseFloat(text) : 0.0
                    }
                    Text { text: "—"; color: Theme.textMuted }
                    TextField {
                        id: maxCaratInput
                        Layout.fillWidth: true
                        placeholderText: "50.00"
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontNormal
                        onEditingFinished: DiamondModel.maxCarat = text.length > 0 ? parseFloat(text) : 999.0
                    }
                }
            }

            ColumnLayout {
                spacing: 4
                Text { text: "Price Range MAD (Min - Max)"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 6
                    TextField {
                        id: minPriceInput
                        Layout.fillWidth: true
                        placeholderText: "0"
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontNormal
                        onEditingFinished: DiamondModel.minPrice = text.length > 0 ? parseFloat(text) : 0.0
                    }
                    Text { text: "—"; color: Theme.textMuted }
                    TextField {
                        id: maxPriceInput
                        Layout.fillWidth: true
                        placeholderText: "Max"
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontNormal
                        onEditingFinished: DiamondModel.maxPrice = text.length > 0 ? parseFloat(text) : 999999999.0
                    }
                }
            }

            ColumnLayout {
                spacing: 4
                Text { text: "Has Image"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                ComboBox {
                    id: imageCombo
                    Layout.fillWidth: true
                    model: ["Any", "With Image", "Without Image"]
                    onCurrentIndexChanged: DiamondModel.hasImage = currentIndex
                }
            }

            ColumnLayout {
                spacing: 4
                Text { text: "Has Certificate"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                ComboBox {
                    id: certCombo
                    Layout.fillWidth: true
                    model: ["Any", "With Certificate", "Without Certificate"]
                    onCurrentIndexChanged: DiamondModel.hasCert = currentIndex
                }
            }

            ColumnLayout {
                spacing: 4
                Text { text: "Archive Status"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                CheckBox {
                    id: archiveCheck
                    text: "Include Archived"
                    checked: DiamondModel.includeArchived
                    onCheckedChanged: DiamondModel.includeArchived = checked
                }
            }

            ColumnLayout {
                Layout.alignment: Qt.AlignBottom
                spacing: 4
                Button {
                    text: "Clear All Filters"
                    Layout.fillWidth: true
                    onClicked: {
                        shapeCombo.currentIndex = 0
                        statusCombo.currentIndex = 0
                        colorCombo.currentIndex = 0
                        clarityCombo.currentIndex = 0
                        cutCombo.currentIndex = 0
                        labCombo.currentIndex = 0
                        imageCombo.currentIndex = 0
                        certCombo.currentIndex = 0
                        archiveCheck.checked = false
                        minCaratInput.text = ""
                        maxCaratInput.text = ""
                        minPriceInput.text = ""
                        maxPriceInput.text = ""
                        DiamondModel.resetFilters()
                    }
                }
            }
        }
    }
}
