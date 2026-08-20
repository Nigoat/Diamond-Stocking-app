import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import DiamondInventory

Dialog {
    id: root

    property var diamondData: ({})
    property bool isEditing: false

    modal: true
    dim: true
    anchors.centerIn: Overlay.overlay
    implicitWidth: Math.min(parent ? parent.width * 0.92 : 900, 920)
    implicitHeight: Math.min(parent ? parent.height * 0.92 : 760, 800)

    background: Rectangle {
        radius: Theme.radiusLarge
        color: Theme.bgCard
        border.color: Theme.border
        border.width: 1
    }

    header: Rectangle {
        width: parent.width
        height: 56
        color: Theme.bgCard
        radius: Theme.radiusLarge

        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: 1
            color: Theme.border
        }

        RowLayout {
            anchors.fill: parent
            anchors.margins: 16

            Text {
                text: root.isEditing ? ("Edit Diamond — " + (root.diamondData.reference || "")) : "Add New Diamond"
                font.pixelSize: Theme.fontLarge
                font.weight: Font.Bold
                color: Theme.textPrimary
            }

            Item { Layout.fillWidth: true }

            Text {
                text: "✕"
                font.pixelSize: 18
                color: Theme.textSecondary
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: root.close()
                }
            }
        }
    }

    contentItem: Flickable {
        clip: true
        contentHeight: formContent.implicitHeight + 24

        ColumnLayout {
            id: formContent
            width: parent.width - 32
            x: 16
            y: 16
            spacing: 20

            Text { text: "Basic Information"; font.pixelSize: Theme.fontMedium; font.weight: Font.Bold; color: Theme.textSecondary }

            GridLayout {
                Layout.fillWidth: true
                columns: 2
                rowSpacing: 12
                columnSpacing: 14

                ColumnLayout {
                    spacing: 4
                    Text { text: "Reference *"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField {
                        id: refField
                        Layout.fillWidth: true
                        placeholderText: "e.g. DMD-00101"
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontNormal
                        text: root.diamondData.reference || AppController.generateNextReference()
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Name *"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField {
                        id: nameField
                        Layout.fillWidth: true
                        placeholderText: "e.g. Round Brilliant Solitaire"
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontNormal
                        text: root.diamondData.name || ""
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "SKU"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField {
                        id: skuField
                        Layout.fillWidth: true
                        placeholderText: "Optional SKU"
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontNormal
                        text: root.diamondData.sku || ""
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Barcode"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField {
                        id: barcodeField
                        Layout.fillWidth: true
                        placeholderText: "Optional barcode"
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontNormal
                        text: root.diamondData.barcode || ""
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 4
                Text { text: "Description"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                ScrollView {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 72
                    TextArea {
                        id: descField
                        placeholderText: "Additional description or notes..."
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontNormal
                        text: root.diamondData.description || ""
                        wrapMode: TextArea.Wrap
                    }
                }
            }

            Rectangle { Layout.fillWidth: true; height: 1; color: Theme.border }
            Text { text: "Diamond Characteristics"; font.pixelSize: Theme.fontMedium; font.weight: Font.Bold; color: Theme.textSecondary }

            GridLayout {
                Layout.fillWidth: true
                columns: 4
                rowSpacing: 12
                columnSpacing: 14

                ColumnLayout {
                    spacing: 4
                    Text { text: "Shape *"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    ComboBox {
                        id: shapeCombo
                        Layout.fillWidth: true
                        model: ["Round", "Princess", "Cushion", "Oval", "Emerald", "Radiant", "Pear", "Marquise", "Asscher", "Heart", "Other"]
                        Component.onCompleted: {
                            var idx = model.indexOf(root.diamondData.shape || "Round")
                            currentIndex = idx >= 0 ? idx : 0
                        }
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Carat Weight *"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField {
                        id: caratField
                        Layout.fillWidth: true
                        placeholderText: "1.00"
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontNormal
                        text: root.diamondData.carat ? Number(root.diamondData.carat).toFixed(2) : "1.00"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Color *"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    ComboBox {
                        id: colorCombo
                        Layout.fillWidth: true
                        model: ["D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "Other"]
                        Component.onCompleted: {
                            var idx = model.indexOf(root.diamondData.color || "G")
                            currentIndex = idx >= 0 ? idx : 3
                        }
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Clarity *"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    ComboBox {
                        id: clarityCombo
                        Layout.fillWidth: true
                        model: ["FL", "IF", "VVS1", "VVS2", "VS1", "VS2", "SI1", "SI2", "I1", "I2", "I3", "Other"]
                        Component.onCompleted: {
                            var idx = model.indexOf(root.diamondData.clarity || "VS1")
                            currentIndex = idx >= 0 ? idx : 4
                        }
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Cut"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    ComboBox {
                        id: cutCombo
                        Layout.fillWidth: true
                        model: ["Excellent", "Very Good", "Good", "Fair", "Poor", "N/A"]
                        Component.onCompleted: {
                            var idx = model.indexOf(root.diamondData.cut || "Excellent")
                            currentIndex = idx >= 0 ? idx : 0
                        }
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Polish"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    ComboBox {
                        id: polishCombo
                        Layout.fillWidth: true
                        model: ["Excellent", "Very Good", "Good", "Fair", "Poor"]
                        Component.onCompleted: {
                            var idx = model.indexOf(root.diamondData.polish || "Excellent")
                            currentIndex = idx >= 0 ? idx : 0
                        }
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Symmetry"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    ComboBox {
                        id: symmetryCombo
                        Layout.fillWidth: true
                        model: ["Excellent", "Very Good", "Good", "Fair", "Poor"]
                        Component.onCompleted: {
                            var idx = model.indexOf(root.diamondData.symmetry || "Very Good")
                            currentIndex = idx >= 0 ? idx : 1
                        }
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Fluorescence"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    ComboBox {
                        id: fluoCombo
                        Layout.fillWidth: true
                        model: ["None", "Faint", "Medium", "Strong", "Very Strong"]
                        Component.onCompleted: {
                            var idx = model.indexOf(root.diamondData.fluorescence || "None")
                            currentIndex = idx >= 0 ? idx : 0
                        }
                    }
                }
            }

            GridLayout {
                Layout.fillWidth: true
                columns: 5
                rowSpacing: 12
                columnSpacing: 14

                ColumnLayout {
                    spacing: 4
                    Text { text: "Table %"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField { id: tableField; Layout.fillWidth: true; placeholderText: "57.0"; color: Theme.textPrimary; font.pixelSize: Theme.fontNormal; text: root.diamondData.tablePercentage ? root.diamondData.tablePercentage.toString() : "" }
                }
                ColumnLayout {
                    spacing: 4
                    Text { text: "Depth %"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField { id: depthField; Layout.fillWidth: true; placeholderText: "62.0"; color: Theme.textPrimary; font.pixelSize: Theme.fontNormal; text: root.diamondData.depthPercentage ? root.diamondData.depthPercentage.toString() : "" }
                }
                ColumnLayout {
                    spacing: 4
                    Text { text: "Length mm"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField { id: lengthField; Layout.fillWidth: true; placeholderText: "6.50"; color: Theme.textPrimary; font.pixelSize: Theme.fontNormal; text: root.diamondData.lengthMm ? root.diamondData.lengthMm.toString() : "" }
                }
                ColumnLayout {
                    spacing: 4
                    Text { text: "Width mm"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField { id: widthField; Layout.fillWidth: true; placeholderText: "6.50"; color: Theme.textPrimary; font.pixelSize: Theme.fontNormal; text: root.diamondData.widthMm ? root.diamondData.widthMm.toString() : "" }
                }
                ColumnLayout {
                    spacing: 4
                    Text { text: "Height mm"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField { id: heightField; Layout.fillWidth: true; placeholderText: "4.00"; color: Theme.textPrimary; font.pixelSize: Theme.fontNormal; text: root.diamondData.heightMm ? root.diamondData.heightMm.toString() : "" }
                }
            }

            Rectangle { Layout.fillWidth: true; height: 1; color: Theme.border }
            Text { text: "Certificate"; font.pixelSize: Theme.fontMedium; font.weight: Font.Bold; color: Theme.textSecondary }

            GridLayout {
                Layout.fillWidth: true
                columns: 3
                rowSpacing: 12
                columnSpacing: 14

                ColumnLayout {
                    spacing: 4
                    Text { text: "Lab"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    ComboBox {
                        id: labCombo
                        Layout.fillWidth: true
                        model: ["None", "GIA", "IGI", "HRD", "GCAL", "Other"]
                        Component.onCompleted: {
                            var idx = model.indexOf(root.diamondData.certLab || "None")
                            currentIndex = idx >= 0 ? idx : 0
                        }
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Certificate Number"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField { id: certNumField; Layout.fillWidth: true; placeholderText: "GIA-1234567890"; color: Theme.textPrimary; font.pixelSize: Theme.fontNormal; text: root.diamondData.certNum || "" }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Certificate Date"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField { id: certDateField; Layout.fillWidth: true; placeholderText: "YYYY-MM-DD"; color: Theme.textPrimary; font.pixelSize: Theme.fontNormal; text: root.diamondData.certDate || "" }
                }
            }

            Rectangle { Layout.fillWidth: true; height: 1; color: Theme.border }
            Text { text: "Pricing (MAD)"; font.pixelSize: Theme.fontMedium; font.weight: Font.Bold; color: Theme.textSecondary }

            GridLayout {
                Layout.fillWidth: true
                columns: 4
                rowSpacing: 12
                columnSpacing: 14

                ColumnLayout {
                    spacing: 4
                    Text { text: "Purchase Cost"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField {
                        id: purchaseField
                        Layout.fillWidth: true
                        placeholderText: "0.00"
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontNormal
                        text: root.diamondData.purchaseCostCents ? (root.diamondData.purchaseCostCents / 100).toFixed(2) : "0.00"
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Selling Price"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField {
                        id: sellingField
                        Layout.fillWidth: true
                        placeholderText: "0.00"
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontNormal
                        text: root.diamondData.sellingPriceCents ? (root.diamondData.sellingPriceCents / 100).toFixed(2) : "0.00"
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Discount Price"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField {
                        id: discountField
                        Layout.fillWidth: true
                        placeholderText: "0.00"
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontNormal
                        text: root.diamondData.discountPriceCents ? (root.diamondData.discountPriceCents / 100).toFixed(2) : "0.00"
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Minimum Price"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField {
                        id: minPriceField
                        Layout.fillWidth: true
                        placeholderText: "0.00"
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontNormal
                        text: root.diamondData.minSellingPriceCents ? (root.diamondData.minSellingPriceCents / 100).toFixed(2) : "0.00"
                    }
                }
            }

            Rectangle { Layout.fillWidth: true; height: 1; color: Theme.border }
            Text { text: "Stock & Location"; font.pixelSize: Theme.fontMedium; font.weight: Font.Bold; color: Theme.textSecondary }

            GridLayout {
                Layout.fillWidth: true
                columns: 3
                rowSpacing: 12
                columnSpacing: 14

                ColumnLayout {
                    spacing: 4
                    Text { text: "Status"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    ComboBox {
                        id: statusCombo
                        Layout.fillWidth: true
                        model: ["Available", "Reserved", "Sold", "Unavailable", "Returned"]
                        Component.onCompleted: {
                            var idx = model.indexOf(root.diamondData.status || "Available")
                            currentIndex = idx >= 0 ? idx : 0
                        }
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Location"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    ComboBox {
                        id: locationCombo
                        Layout.fillWidth: true
                        model: ["Store", "Main Vault", "Safe Deposit", "Display Case 1", "Display Case 2", "Workshop", "Other"]
                        Component.onCompleted: {
                            var idx = model.indexOf(root.diamondData.location || "Store")
                            currentIndex = idx >= 0 ? idx : 0
                        }
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Location Details"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField { id: locationDetailsField; Layout.fillWidth: true; placeholderText: "Tray A / Slot 3"; color: Theme.textPrimary; font.pixelSize: Theme.fontNormal; text: root.diamondData.locationDetails || "" }
                }
            }

            Rectangle { Layout.fillWidth: true; height: 1; color: Theme.border }
            Text { text: "Supplier"; font.pixelSize: Theme.fontMedium; font.weight: Font.Bold; color: Theme.textSecondary }

            ComboBox {
                id: supplierCombo
                Layout.fillWidth: true
                model: {
                    var items = ["None"]
                    for (var i = 0; i < SupplierModel.count; ++i) {
                        var s = SupplierModel.getAt(i)
                        items.push(s.name + (s.company ? " (" + s.company + ")" : ""))
                    }
                    return items
                }
            }

            Item { Layout.preferredHeight: 16 }
        }
    }

    footer: Rectangle {
        width: parent.width
        height: 60
        color: Theme.bgCard
        border.color: Theme.border
        border.width: 1
        radius: Theme.radiusLarge

        RowLayout {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 12

            Text {
                text: validationMsg
                font.pixelSize: Theme.fontSmall
                color: Theme.danger
                visible: validationMsg.length > 0
            }

            Item { Layout.fillWidth: true }

            Button {
                text: "Cancel"
                onClicked: root.close()
            }

            Button {
                text: root.isEditing ? "Save Changes" : "Add Diamond"
                highlighted: true
                onClicked: root.submitForm()
            }
        }
    }

    property string validationMsg: ""

    function openNew() {
        root.isEditing = false
        root.diamondData = {}
        root.validationMsg = ""
        refField.text = AppController.generateNextReference()
        nameField.text = ""
        descField.text = ""
        caratField.text = "1.00"
        shapeCombo.currentIndex = 0
        colorCombo.currentIndex = 3
        clarityCombo.currentIndex = 4
        cutCombo.currentIndex = 0
        polishCombo.currentIndex = 0
        symmetryCombo.currentIndex = 1
        fluoCombo.currentIndex = 0
        purchaseField.text = "0.00"
        sellingField.text = "0.00"
        discountField.text = "0.00"
        minPriceField.text = "0.00"
        statusCombo.currentIndex = 0
        locationCombo.currentIndex = 0
        locationDetailsField.text = ""
        certNumField.text = ""
        certDateField.text = ""
        labCombo.currentIndex = 0
        root.open()
    }

    function openEdit(data) {
        root.isEditing = true
        root.diamondData = data
        root.validationMsg = ""
        refField.text = data.reference || ""
        nameField.text = data.name || ""
        descField.text = data.description || ""
        caratField.text = data.carat ? Number(data.carat).toFixed(2) : "1.00"
        var si = ["Round", "Princess", "Cushion", "Oval", "Emerald", "Radiant", "Pear", "Marquise", "Asscher", "Heart", "Other"].indexOf(data.shape || "Round")
        shapeCombo.currentIndex = si >= 0 ? si : 0
        var ci = ["D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "Other"].indexOf(data.color || "G")
        colorCombo.currentIndex = ci >= 0 ? ci : 3
        var cai = ["FL", "IF", "VVS1", "VVS2", "VS1", "VS2", "SI1", "SI2", "I1", "I2", "I3", "Other"].indexOf(data.clarity || "VS1")
        clarityCombo.currentIndex = cai >= 0 ? cai : 4
        var cuti = ["Excellent", "Very Good", "Good", "Fair", "Poor", "N/A"].indexOf(data.cut || "Excellent")
        cutCombo.currentIndex = cuti >= 0 ? cuti : 0
        purchaseField.text = data.purchaseCostCents ? (data.purchaseCostCents / 100).toFixed(2) : "0.00"
        sellingField.text = data.sellingPriceCents ? (data.sellingPriceCents / 100).toFixed(2) : "0.00"
        discountField.text = data.discountPriceCents ? (data.discountPriceCents / 100).toFixed(2) : "0.00"
        minPriceField.text = data.minSellingPriceCents ? (data.minSellingPriceCents / 100).toFixed(2) : "0.00"
        var sti = ["Available", "Reserved", "Sold", "Unavailable", "Returned"].indexOf(data.status || "Available")
        statusCombo.currentIndex = sti >= 0 ? sti : 0
        var li = ["Store", "Main Vault", "Safe Deposit", "Display Case 1", "Display Case 2", "Workshop", "Other"].indexOf(data.location || "Store")
        locationCombo.currentIndex = li >= 0 ? li : 0
        locationDetailsField.text = data.locationDetails || ""
        certNumField.text = data.certNum || ""
        certDateField.text = data.certDate || ""
        skuField.text = data.sku || ""
        barcodeField.text = data.barcode || ""
        tableField.text = data.tablePercentage ? data.tablePercentage.toString() : ""
        depthField.text = data.depthPercentage ? data.depthPercentage.toString() : ""
        lengthField.text = data.lengthMm ? data.lengthMm.toString() : ""
        widthField.text = data.widthMm ? data.widthMm.toString() : ""
        heightField.text = data.heightMm ? data.heightMm.toString() : ""
        root.open()
    }

    function submitForm() {
        validationMsg = ""

        if (refField.text.trim().length === 0) {
            validationMsg = "Reference is required."
            return
        }
        if (nameField.text.trim().length === 0) {
            validationMsg = "Name is required."
            return
        }
        var ct = parseFloat(caratField.text)
        if (isNaN(ct) || ct < 0) {
            validationMsg = "Carat weight must be a valid positive number."
            return
        }
        var pCost = parseFloat(purchaseField.text)
        var sCost = parseFloat(sellingField.text)
        if (isNaN(pCost) || pCost < 0 || isNaN(sCost) || sCost < 0) {
            validationMsg = "Prices must be valid non-negative numbers."
            return
        }

        var supplierId = 0
        if (supplierCombo.currentIndex > 0 && supplierCombo.currentIndex <= SupplierModel.count) {
            supplierId = SupplierModel.getAt(supplierCombo.currentIndex - 1).supplierId
        }

        var data = {
            id: root.isEditing ? (root.diamondData.diamondId || 0) : 0,
            reference: refField.text.trim(),
            sku: skuField.text.trim(),
            barcode: barcodeField.text.trim(),
            name: nameField.text.trim(),
            description: descField.text.trim(),
            shape: shapeCombo.currentText,
            caratWeight: ct,
            color: colorCombo.currentText,
            clarity: clarityCombo.currentText,
            cut: cutCombo.currentText,
            polish: polishCombo.currentText,
            symmetry: symmetryCombo.currentText,
            fluorescence: fluoCombo.currentText,
            tablePercentage: parseFloat(tableField.text) || 0,
            depthPercentage: parseFloat(depthField.text) || 0,
            lengthMm: parseFloat(lengthField.text) || 0,
            widthMm: parseFloat(widthField.text) || 0,
            heightMm: parseFloat(heightField.text) || 0,
            certificateLab: labCombo.currentText,
            certificateNumber: certNumField.text.trim(),
            certificateDate: certDateField.text.trim(),
            purchasePriceCents: Math.round(pCost * 100),
            sellingPriceCents: Math.round(sCost * 100),
            discountPriceCents: Math.round((parseFloat(discountField.text) || 0) * 100),
            minSellingPriceCents: Math.round((parseFloat(minPriceField.text) || 0) * 100),
            status: statusCombo.currentText,
            location: locationCombo.currentText,
            locationDetails: locationDetailsField.text.trim(),
            supplierId: supplierId,
            isFavorite: root.diamondData.isFavorite || false,
            archived: root.diamondData.archived || false
        }

        var ok = AppController.saveDiamond(data)
        if (ok) {
            root.close()
        }
    }
}
