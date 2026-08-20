import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import QtQuick.Dialogs
import DiamondInventory

Rectangle {
    id: root

    signal openDiamondDetails(int diamondId)

    color: Theme.bgPrimary

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.fillWidth: true
            height: 60
            color: Theme.bgSecondary
            border.color: Theme.border
            border.width: 0

            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 1
                color: Theme.border
            }

            RowLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 12

                SearchBar {
                    id: globalSearch
                    Layout.preferredWidth: 380
                    onTextModified: (t) => { DiamondModel.currentSearch = t }
                }

                Button {
                    text: (filterPanel.isExpanded ? "▲ Filters" : "▼ Filters") + (hasActiveFilters() ? " ●" : "")
                    checkable: true
                    checked: filterPanel.isExpanded
                    onClicked: filterPanel.isExpanded = !filterPanel.isExpanded

                    function hasActiveFilters() {
                        return DiamondModel.currentStatus !== "" && DiamondModel.currentStatus !== "All"
                            || DiamondModel.currentShape !== "" && DiamondModel.currentShape !== "All"
                            || DiamondModel.currentColor !== "" && DiamondModel.currentColor !== "All"
                            || DiamondModel.currentClarity !== "" && DiamondModel.currentClarity !== "All"
                    }
                }

                Item { Layout.fillWidth: true }

                Text {
                    text: DiamondModel.count + " diamonds"
                    font.pixelSize: Theme.fontSmall
                    color: Theme.textMuted
                }

                Rectangle {
                    width: 1
                    height: 24
                    color: Theme.border
                }

                Row {
                    spacing: 4

                    Rectangle {
                        width: 34
                        height: 34
                        radius: Theme.radiusSmall
                        color: viewMode === "table" ? Theme.accentLight : "transparent"
                        border.color: viewMode === "table" ? Theme.accent : Theme.border
                        border.width: 1

                        Text {
                            anchors.centerIn: parent
                            text: "≡"
                            font.pixelSize: 18
                            color: viewMode === "table" ? Theme.accent : Theme.textSecondary
                        }

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                viewMode = "table"
                                Settings.viewMode = "table"
                            }
                        }
                    }

                    Rectangle {
                        width: 34
                        height: 34
                        radius: Theme.radiusSmall
                        color: viewMode === "cards" ? Theme.accentLight : "transparent"
                        border.color: viewMode === "cards" ? Theme.accent : Theme.border
                        border.width: 1

                        Text {
                            anchors.centerIn: parent
                            text: "⊞"
                            font.pixelSize: 16
                            color: viewMode === "cards" ? Theme.accent : Theme.textSecondary
                        }

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                viewMode = "cards"
                                Settings.viewMode = "cards"
                            }
                        }
                    }
                }

                Rectangle {
                    width: 1
                    height: 24
                    color: Theme.border
                }

                Button {
                    text: "+ Add Diamond"
                    highlighted: true
                    onClicked: addEditModal.openNew()
                }

                Button {
                    text: "⤓ Export"
                    onClicked: exportFileDialog.open()
                }

                Button {
                    text: "⤒ Import"
                    onClicked: importFileDialog.open()
                }
            }
        }

        FilterPanel {
            id: filterPanel
            Layout.fillWidth: true
        }

        Rectangle {
            Layout.fillWidth: true
            height: DiamondModel.selectedCount > 0 ? 44 : 0
            color: Theme.accentLight
            visible: height > 0
            clip: true

            Behavior on height { NumberAnimation { duration: 200 } }

            RowLayout {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 12

                Text {
                    text: DiamondModel.selectedCount + " diamonds selected"
                    font.pixelSize: Theme.fontNormal
                    font.weight: Font.DemiBold
                    color: Theme.accent
                }

                Item { Layout.fillWidth: true }

                Button {
                    text: "Archive Selected"
                    onClicked: {
                        confirmBulkDialog.titleText = "Archive " + DiamondModel.selectedCount + " Diamonds"
                        confirmBulkDialog.messageText = "This will archive the selected diamonds. They can be restored later."
                        confirmBulkDialog.isDestructive = true
                        confirmBulkDialog.confirmAction = function() {
                            AppController.bulkArchive(DiamondModel.selectedIds(), true)
                        }
                        confirmBulkDialog.open()
                    }
                }

                Button {
                    text: "Mark Available"
                    onClicked: AppController.bulkUpdateStatus(DiamondModel.selectedIds(), "Available")
                }

                Button {
                    text: "Mark Sold"
                    onClicked: AppController.bulkUpdateStatus(DiamondModel.selectedIds(), "Sold")
                }

                Button {
                    text: "Clear Selection"
                    onClicked: DiamondModel.clearSelection()
                }
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            property string viewMode: Settings.viewMode || "table"

            DiamondTable {
                id: tableView
                anchors.fill: parent
                visible: parent.viewMode === "table"
                onOpenDetails: (id) => root.openDiamondDetails(id)
                onContextMenuRequested: (id, mx, my) => {
                    contextMenu.targetId = id
                    contextMenu.x = mx
                    contextMenu.y = my
                    contextMenu.open()
                }
            }

            ScrollView {
                id: gridScrollView
                anchors.fill: parent
                visible: parent.viewMode === "cards"
                clip: true

                GridView {
                    id: gridView
                    anchors.fill: parent
                    anchors.margins: 16
                    cellWidth: 280
                    cellHeight: 350
                    model: DiamondModel

                    delegate: DiamondCard {
                        width: 264
                        height: 334
                        diamondData: DiamondModel.getAt(index)
                        onOpenDetails: (id) => root.openDiamondDetails(id)
                        onContextMenuRequested: (id, mx, my) => {
                            contextMenu.targetId = id
                            contextMenu.open()
                        }
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: "No diamonds found.\n\nTry adjusting your search or filters."
                    font.pixelSize: Theme.fontLarge
                    color: Theme.textMuted
                    horizontalAlignment: Text.AlignHCenter
                    lineHeight: 1.5
                    visible: DiamondModel.count === 0
                }
            }

            Text {
                anchors.centerIn: parent
                text: "No diamonds found.\n\nTry adjusting your search or filters."
                font.pixelSize: Theme.fontLarge
                color: Theme.textMuted
                horizontalAlignment: Text.AlignHCenter
                lineHeight: 1.5
                visible: DiamondModel.count === 0
                z: 10
            }
        }
    }

    property string viewMode: Settings.viewMode || "table"

    Menu {
        id: contextMenu

        property int targetId: 0

        MenuItem {
            text: "View Details"
            onClicked: root.openDiamondDetails(contextMenu.targetId)
        }
        MenuItem {
            text: "Edit Diamond"
            onClicked: {
                var data = DiamondModel.getById(contextMenu.targetId)
                addEditModal.openEdit(data)
            }
        }
        MenuSeparator {}
        MenuItem {
            text: "Mark Available"
            onClicked: AppController.updateDiamondStatus(contextMenu.targetId, "Available")
        }
        MenuItem {
            text: "Mark Reserved"
            onClicked: AppController.updateDiamondStatus(contextMenu.targetId, "Reserved")
        }
        MenuItem {
            text: "Mark Sold"
            onClicked: AppController.updateDiamondStatus(contextMenu.targetId, "Sold")
        }
        MenuSeparator {}
        MenuItem {
            text: "Duplicate"
            onClicked: AppController.duplicateDiamond(contextMenu.targetId)
        }
        MenuItem {
            text: "Print Spec Sheet"
            onClicked: AppController.printDiamondSheet(contextMenu.targetId, "")
        }
        MenuSeparator {}
        MenuItem {
            text: "Archive"
            onClicked: {
                confirmBulkDialog.titleText = "Archive Diamond"
                confirmBulkDialog.messageText = "This will archive the diamond. It can be restored from Settings."
                confirmBulkDialog.isDestructive = true
                confirmBulkDialog.confirmAction = function() {
                    AppController.archiveDiamond(contextMenu.targetId)
                }
                confirmBulkDialog.open()
            }
        }
    }

    ConfirmDialog {
        id: confirmBulkDialog
        property var confirmAction: null
        titleText: ""
        messageText: ""
        confirmButtonText: "Confirm"
        isDestructive: false
        onConfirmed: {
            if (confirmAction) confirmAction()
        }
    }

    AddEditDiamondModal {
        id: addEditModal
        anchors.centerIn: parent
    }

    FileDialog {
        id: exportFileDialog
        title: "Export Inventory as CSV"
        fileMode: FileDialog.SaveFile
        nameFilters: ["CSV Files (*.csv)", "All Files (*)"]
        currentFolder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            AppController.exportCsv(selectedFile.toString())
        }
    }

    FileDialog {
        id: importFileDialog
        title: "Import Diamonds from CSV"
        nameFilters: ["CSV Files (*.csv)"]
        onAccepted: {
            var preview = AppController.previewImportCsv(selectedFile.toString())
            importResultDialog.previewData = preview
            importResultDialog.filePath = selectedFile.toString()
            importResultDialog.open()
        }
    }

    Dialog {
        id: importResultDialog
        property var previewData: ({})
        property string filePath: ""

        modal: true
        anchors.centerIn: parent
        title: "Import Preview"
        implicitWidth: 500
        implicitHeight: 280

        contentItem: Column {
            spacing: 12
            padding: 16

            Text {
                text: importResultDialog.previewData.success ?
                    ("Found " + (importResultDialog.previewData.totalRows || 0) + " rows to import.") :
                    ("Error: " + (importResultDialog.previewData.errorMessage || "Unknown error"))
                font.pixelSize: Theme.fontNormal
                color: importResultDialog.previewData.success ? Theme.textPrimary : Theme.danger
                wrapMode: Text.WordWrap
                width: parent.width - 32
            }

            Text {
                text: "Headers detected: " + (importResultDialog.previewData.headers ? importResultDialog.previewData.headers.join(", ") : "None")
                font.pixelSize: Theme.fontSmall
                color: Theme.textSecondary
                wrapMode: Text.WordWrap
                width: parent.width - 32
                visible: importResultDialog.previewData.success
            }

            Row {
                spacing: 12
                visible: importResultDialog.previewData.success

                Button {
                    text: "Import All Valid Rows"
                    highlighted: true
                    onClicked: {
                        importResultDialog.close()
                        var result = AppController.executeImportCsv(importResultDialog.filePath, {})
                        importDoneDialog.result = result
                        importDoneDialog.open()
                    }
                }

                Button {
                    text: "Cancel"
                    onClicked: importResultDialog.close()
                }
            }
        }
    }

    Dialog {
        id: importDoneDialog
        property var result: ({})
        modal: true
        anchors.centerIn: parent
        title: "Import Complete"
        implicitWidth: 420
        implicitHeight: 240

        contentItem: Column {
            spacing: 10
            padding: 16

            Text {
                text: "Import Results"
                font.pixelSize: Theme.fontLarge
                font.weight: Font.Bold
                color: Theme.textPrimary
            }

            Text {
                text: "✓ Imported: " + (importDoneDialog.result.importedCount || 0) + " diamonds"
                font.pixelSize: Theme.fontNormal
                color: Theme.success
            }

            Text {
                text: "⚠ Warnings: " + (importDoneDialog.result.warningCount || 0)
                font.pixelSize: Theme.fontNormal
                color: Theme.warning
                visible: (importDoneDialog.result.warningCount || 0) > 0
            }

            Text {
                text: "✕ Errors: " + (importDoneDialog.result.errorCount || 0)
                font.pixelSize: Theme.fontNormal
                color: Theme.danger
                visible: (importDoneDialog.result.errorCount || 0) > 0
            }

            Button {
                text: "Done"
                onClicked: importDoneDialog.close()
            }
        }
    }
}
