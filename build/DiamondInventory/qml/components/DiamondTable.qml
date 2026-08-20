import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import DiamondInventory

Item {
    id: root

    signal openDetails(int diamondId)
    signal editDiamond(int diamondId)
    signal contextMenuRequested(int diamondId, real mouseX, real mouseY)

    Rectangle {
        id: tableHeader
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 38
        color: Theme.bgInput
        border.color: Theme.border
        border.width: 1
        z: 2

        Row {
            anchors.fill: parent
            anchors.leftMargin: 12
            anchors.rightMargin: 12
            spacing: 8

            Item {
                width: 32
                height: parent.height
                CheckBox {
                    anchors.centerIn: parent
                    checked: DiamondModel.selectedCount > 0 && DiamondModel.selectedCount === DiamondModel.count
                    onToggled: {
                        if (checked) DiamondModel.selectAll()
                        else DiamondModel.clearSelection()
                    }
                }
            }

            Item {
                width: 44
                height: parent.height
                Text { text: "Photo"; font.pixelSize: Theme.fontSmall; font.weight: Font.Bold; color: Theme.textSecondary; anchors.verticalCenter: parent.verticalCenter }
            }

            Item {
                width: 110
                height: parent.height
                Text { text: "Reference " + (DiamondModel.sortBy === "reference" ? (DiamondModel.sortAscending ? "▲" : "▼") : ""); font.pixelSize: Theme.fontSmall; font.weight: Font.Bold; color: Theme.textSecondary; anchors.verticalCenter: parent.verticalCenter }
                MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: { if (DiamondModel.sortBy === "reference") DiamondModel.sortAscending = !DiamondModel.sortAscending; else { DiamondModel.sortBy = "reference"; DiamondModel.sortAscending = true; } } }
            }

            Item {
                width: 160
                height: parent.height
                Text { text: "Name " + (DiamondModel.sortBy === "name" ? (DiamondModel.sortAscending ? "▲" : "▼") : ""); font.pixelSize: Theme.fontSmall; font.weight: Font.Bold; color: Theme.textSecondary; anchors.verticalCenter: parent.verticalCenter }
                MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: { if (DiamondModel.sortBy === "name") DiamondModel.sortAscending = !DiamondModel.sortAscending; else { DiamondModel.sortBy = "name"; DiamondModel.sortAscending = true; } } }
            }

            Item {
                width: 80
                height: parent.height
                Text { text: "Shape"; font.pixelSize: Theme.fontSmall; font.weight: Font.Bold; color: Theme.textSecondary; anchors.verticalCenter: parent.verticalCenter }
            }

            Item {
                width: 70
                height: parent.height
                Text { text: "Carat " + (DiamondModel.sortBy === "carat" ? (DiamondModel.sortAscending ? "▲" : "▼") : ""); font.pixelSize: Theme.fontSmall; font.weight: Font.Bold; color: Theme.textSecondary; anchors.verticalCenter: parent.verticalCenter }
                MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: { if (DiamondModel.sortBy === "carat") DiamondModel.sortAscending = !DiamondModel.sortAscending; else { DiamondModel.sortBy = "carat"; DiamondModel.sortAscending = false; } } }
            }

            Item {
                width: 60
                height: parent.height
                Text { text: "Color"; font.pixelSize: Theme.fontSmall; font.weight: Font.Bold; color: Theme.textSecondary; anchors.verticalCenter: parent.verticalCenter }
            }

            Item {
                width: 65
                height: parent.height
                Text { text: "Clarity"; font.pixelSize: Theme.fontSmall; font.weight: Font.Bold; color: Theme.textSecondary; anchors.verticalCenter: parent.verticalCenter }
            }

            Item {
                width: 80
                height: parent.height
                Text { text: "Cut"; font.pixelSize: Theme.fontSmall; font.weight: Font.Bold; color: Theme.textSecondary; anchors.verticalCenter: parent.verticalCenter }
            }

            Item {
                width: 100
                height: parent.height
                Text { text: "Certificate"; font.pixelSize: Theme.fontSmall; font.weight: Font.Bold; color: Theme.textSecondary; anchors.verticalCenter: parent.verticalCenter }
            }

            Item {
                width: 110
                height: parent.height
                Text { text: "Purchase Cost"; font.pixelSize: Theme.fontSmall; font.weight: Font.Bold; color: Theme.textSecondary; anchors.verticalCenter: parent.verticalCenter }
            }

            Item {
                width: 120
                height: parent.height
                Text { text: "Selling Price " + (DiamondModel.sortBy === "price" ? (DiamondModel.sortAscending ? "▲" : "▼") : ""); font.pixelSize: Theme.fontSmall; font.weight: Font.Bold; color: Theme.textSecondary; anchors.verticalCenter: parent.verticalCenter }
                MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: { if (DiamondModel.sortBy === "price") DiamondModel.sortAscending = !DiamondModel.sortAscending; else { DiamondModel.sortBy = "price"; DiamondModel.sortAscending = false; } } }
            }

            Item {
                width: 110
                height: parent.height
                Text { text: "Status " + (DiamondModel.sortBy === "status" ? (DiamondModel.sortAscending ? "▲" : "▼") : ""); font.pixelSize: Theme.fontSmall; font.weight: Font.Bold; color: Theme.textSecondary; anchors.verticalCenter: parent.verticalCenter }
                MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: { if (DiamondModel.sortBy === "status") DiamondModel.sortAscending = !DiamondModel.sortAscending; else { DiamondModel.sortBy = "status"; DiamondModel.sortAscending = true; } } }
            }

            Item {
                width: 110
                height: parent.height
                Text { text: "Location"; font.pixelSize: Theme.fontSmall; font.weight: Font.Bold; color: Theme.textSecondary; anchors.verticalCenter: parent.verticalCenter }
            }
        }
    }

    ListView {
        id: tableList
        anchors.top: tableHeader.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        clip: true
        model: DiamondModel

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
        }

        delegate: Rectangle {
            id: rowItem
            width: tableList.width
            height: 44
            color: selected ? Theme.bgSelected : (rowMouse.containsMouse ? Theme.bgHover : (index % 2 === 0 ? Theme.bgCard : Theme.bgPrimary))
            border.color: Theme.border
            border.width: 0

            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 1
                color: Theme.border
            }

            Row {
                anchors.fill: parent
                anchors.leftMargin: 12
                anchors.rightMargin: 12
                spacing: 8

                Item {
                    width: 32
                    height: parent.height
                    CheckBox {
                        anchors.centerIn: parent
                        checked: selected
                        onToggled: DiamondModel.toggleSelection(diamondId)
                    }
                }

                Item {
                    width: 44
                    height: parent.height
                    Rectangle {
                        width: 32
                        height: 32
                        radius: Theme.radiusSmall
                        color: Theme.bgInput
                        anchors.centerIn: parent
                        clip: true

                        Image {
                            anchors.fill: parent
                            source: mainThumbnail ? ("file://" + mainThumbnail) : ""
                            fillMode: Image.PreserveAspectCrop
                            asynchronous: true
                            visible: source.toString().length > 0 && status === Image.Ready
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "💎"
                            font.pixelSize: 14
                            visible: !mainThumbnail
                            opacity: 0.5
                        }
                    }
                }

                Item {
                    width: 110
                    height: parent.height
                    Text {
                        text: reference
                        font.pixelSize: Theme.fontNormal
                        font.weight: Font.DemiBold
                        color: Theme.accent
                        elide: Text.ElideRight
                        width: parent.width
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Item {
                    width: 160
                    height: parent.height
                    Text {
                        text: name
                        font.pixelSize: Theme.fontNormal
                        color: Theme.textPrimary
                        elide: Text.ElideRight
                        width: parent.width
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Item {
                    width: 80
                    height: parent.height
                    Text {
                        text: shape
                        font.pixelSize: Theme.fontSmall
                        color: Theme.textSecondary
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Item {
                    width: 70
                    height: parent.height
                    Text {
                        text: Number(carat).toFixed(2) + " ct"
                        font.pixelSize: Theme.fontNormal
                        font.weight: Font.Medium
                        color: Theme.textPrimary
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Item {
                    width: 60
                    height: parent.height
                    Text {
                        text: color
                        font.pixelSize: Theme.fontNormal
                        color: Theme.textPrimary
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Item {
                    width: 65
                    height: parent.height
                    Text {
                        text: clarity
                        font.pixelSize: Theme.fontNormal
                        color: Theme.textPrimary
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Item {
                    width: 80
                    height: parent.height
                    Text {
                        text: cut
                        font.pixelSize: Theme.fontSmall
                        color: Theme.textSecondary
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Item {
                    width: 100
                    height: parent.height
                    Text {
                        text: certNum ? (certLab + " " + certNum) : "-"
                        font.pixelSize: Theme.fontSmall
                        color: Theme.textSecondary
                        elide: Text.ElideRight
                        width: parent.width
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Item {
                    width: 110
                    height: parent.height
                    Text {
                        text: purchaseCostFormatted
                        font.pixelSize: Theme.fontSmall
                        color: Theme.textMuted
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Item {
                    width: 120
                    height: parent.height
                    Text {
                        text: sellingPriceFormatted
                        font.pixelSize: Theme.fontNormal
                        font.weight: Font.Bold
                        color: Theme.textPrimary
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Item {
                    width: 110
                    height: parent.height
                    StatusBadge {
                        status: model.status
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Item {
                    width: 110
                    height: parent.height
                    Text {
                        text: location
                        font.pixelSize: Theme.fontSmall
                        color: Theme.textSecondary
                        elide: Text.ElideRight
                        width: parent.width
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }

            MouseArea {
                id: rowMouse
                anchors.fill: parent
                hoverEnabled: true
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                cursorShape: Qt.PointingHandCursor

                onDoubleClicked: {
                    root.openDetails(diamondId)
                }

                onClicked: (mouse) => {
                    if (mouse.button === Qt.RightButton) {
                        root.contextMenuRequested(diamondId, mouse.x, rowItem.y + mouse.y)
                    }
                }
            }
        }
    }
}
