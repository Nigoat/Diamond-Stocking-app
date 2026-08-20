import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import DiamondInventory

Rectangle {
    id: root
    color: Theme.bgPrimary

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        RowLayout {
            Layout.fillWidth: true

            Text {
                text: "Suppliers"
                font.pixelSize: Theme.fontTitle
                font.weight: Font.Bold
                color: Theme.textPrimary
            }

            Item { Layout.fillWidth: true }

            TextField {
                id: supplierSearch
                placeholderText: "Search suppliers..."
                color: Theme.textPrimary
                font.pixelSize: Theme.fontNormal
                Layout.preferredWidth: 260
                onTextChanged: SupplierModel.search = text
            }

            Button {
                text: "+ Add Supplier"
                highlighted: true
                onClicked: editSupplierDialog.openNew()
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: Theme.radiusLarge
            color: Theme.bgCard
            border.color: Theme.border
            border.width: 1
            clip: true

            ListView {
                id: supplierList
                anchors.fill: parent
                model: SupplierModel
                clip: true

                ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded }

                delegate: Rectangle {
                    width: supplierList.width
                    height: 60
                    color: supplierMouse.containsMouse ? Theme.bgHover : "transparent"

                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 1
                        color: Theme.border
                    }

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 16
                        spacing: 16

                        Rectangle {
                            width: 40
                            height: 40
                            radius: 20
                            color: Theme.accentLight

                            Text {
                                anchors.centerIn: parent
                                text: name.charAt(0).toUpperCase()
                                font.pixelSize: Theme.fontLarge
                                font.weight: Font.Bold
                                color: Theme.accent
                            }
                        }

                        ColumnLayout {
                            spacing: 2
                            Layout.fillWidth: true

                            Text {
                                text: name
                                font.pixelSize: Theme.fontNormal
                                font.weight: Font.Bold
                                color: Theme.textPrimary
                            }

                            Text {
                                text: company + (country ? " • " + country : "") + (email ? " • " + email : "")
                                font.pixelSize: Theme.fontSmall
                                color: Theme.textSecondary
                                elide: Text.ElideRight
                                Layout.fillWidth: true
                            }
                        }

                        Column {
                            spacing: 2

                            Text {
                                text: diamondCount + " diamonds"
                                font.pixelSize: Theme.fontSmall
                                color: Theme.textSecondary
                                horizontalAlignment: Text.AlignRight
                                width: parent.width
                            }

                            Text {
                                text: totalCostFormatted
                                font.pixelSize: Theme.fontNormal
                                font.weight: Font.DemiBold
                                color: Theme.textPrimary
                                horizontalAlignment: Text.AlignRight
                                width: parent.width
                            }
                        }

                        Row {
                            spacing: 6

                            Button {
                                text: "Edit"
                                onClicked: {
                                    var data = SupplierModel.getAt(index)
                                    editSupplierDialog.openEdit(data)
                                }
                            }

                            Button {
                                text: "Delete"
                                onClicked: {
                                    deleteConfirm.targetId = supplierId
                                    deleteConfirm.open()
                                }
                            }
                        }
                    }

                    MouseArea {
                        id: supplierMouse
                        anchors.fill: parent
                        hoverEnabled: true
                        propagateComposedEvents: true
                        onClicked: (mouse) => mouse.accepted = false
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: "No suppliers yet.\n\nAdd your first supplier to track purchases."
                    font.pixelSize: Theme.fontLarge
                    color: Theme.textMuted
                    horizontalAlignment: Text.AlignHCenter
                    lineHeight: 1.5
                    visible: SupplierModel.count === 0
                }
            }
        }
    }

    Dialog {
        id: editSupplierDialog
        modal: true
        anchors.centerIn: parent
        implicitWidth: 520
        implicitHeight: 500

        property bool isEditing: false
        property var supplierData: ({})

        background: Rectangle {
            radius: Theme.radiusLarge
            color: Theme.bgCard
            border.color: Theme.border
        }

        header: Text {
            text: editSupplierDialog.isEditing ? "Edit Supplier" : "Add Supplier"
            font.pixelSize: Theme.fontLarge
            font.weight: Font.Bold
            color: Theme.textPrimary
            padding: 20
        }

        contentItem: ColumnLayout {
            spacing: 12
            padding: 16

            GridLayout {
                Layout.fillWidth: true
                columns: 2
                rowSpacing: 10
                columnSpacing: 12

                ColumnLayout {
                    spacing: 4
                    Text { text: "Name *"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField { id: supNameField; Layout.fillWidth: true; color: Theme.textPrimary; font.pixelSize: Theme.fontNormal; text: editSupplierDialog.supplierData.name || "" }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Company"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField { id: supCompanyField; Layout.fillWidth: true; color: Theme.textPrimary; font.pixelSize: Theme.fontNormal; text: editSupplierDialog.supplierData.company || "" }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Phone"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField { id: supPhoneField; Layout.fillWidth: true; color: Theme.textPrimary; font.pixelSize: Theme.fontNormal; text: editSupplierDialog.supplierData.phone || "" }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Email"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField { id: supEmailField; Layout.fillWidth: true; color: Theme.textPrimary; font.pixelSize: Theme.fontNormal; text: editSupplierDialog.supplierData.email || "" }
                }

                ColumnLayout {
                    spacing: 4
                    Text { text: "Country"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField { id: supCountryField; Layout.fillWidth: true; color: Theme.textPrimary; font.pixelSize: Theme.fontNormal; text: editSupplierDialog.supplierData.country || "" }
                }

                ColumnLayout {
                    Layout.columnSpan: 2
                    spacing: 4
                    Text { text: "Address"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextField { id: supAddressField; Layout.fillWidth: true; color: Theme.textPrimary; font.pixelSize: Theme.fontNormal; text: editSupplierDialog.supplierData.address || "" }
                }

                ColumnLayout {
                    Layout.columnSpan: 2
                    spacing: 4
                    Text { text: "Notes"; font.pixelSize: Theme.fontSmall; font.weight: Font.DemiBold; color: Theme.textSecondary }
                    TextArea { id: supNotesField; Layout.fillWidth: true; color: Theme.textPrimary; font.pixelSize: Theme.fontNormal; text: editSupplierDialog.supplierData.notes || ""; Layout.preferredHeight: 72 }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                Item { Layout.fillWidth: true }
                Button {
                    text: "Cancel"
                    onClicked: editSupplierDialog.close()
                }
                Button {
                    text: editSupplierDialog.isEditing ? "Save Changes" : "Add Supplier"
                    highlighted: true
                    onClicked: {
                        if (supNameField.text.trim().length === 0) return
                        var data = {
                            id: editSupplierDialog.isEditing ? (editSupplierDialog.supplierData.supplierId || 0) : 0,
                            name: supNameField.text.trim(),
                            company: supCompanyField.text.trim(),
                            phone: supPhoneField.text.trim(),
                            email: supEmailField.text.trim(),
                            address: supAddressField.text.trim(),
                            country: supCountryField.text.trim(),
                            notes: supNotesField.text.trim()
                        }
                        AppController.saveSupplier(data)
                        editSupplierDialog.close()
                    }
                }
            }
        }

        function openNew() {
            isEditing = false
            supplierData = {}
            supNameField.text = ""
            supCompanyField.text = ""
            supPhoneField.text = ""
            supEmailField.text = ""
            supAddressField.text = ""
            supCountryField.text = ""
            supNotesField.text = ""
            open()
        }

        function openEdit(data) {
            isEditing = true
            supplierData = data
            supNameField.text = data.name || ""
            supCompanyField.text = data.company || ""
            supPhoneField.text = data.phone || ""
            supEmailField.text = data.email || ""
            supAddressField.text = data.address || ""
            supCountryField.text = data.country || ""
            supNotesField.text = data.notes || ""
            open()
        }
    }

    ConfirmDialog {
        id: deleteConfirm
        property int targetId: 0
        titleText: "Delete Supplier"
        messageText: "This will remove the supplier. Diamonds linked to this supplier will lose their supplier reference."
        confirmButtonText: "Delete"
        isDestructive: true
        onConfirmed: AppController.deleteSupplier(targetId)
    }
}
