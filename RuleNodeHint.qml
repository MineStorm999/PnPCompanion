import QtQuick 2.15
import QtQuick.Controls 2.15
import PnPCompanion
import QtQuick.Layouts
import QtQuick.Effects

ToolTip {
    id: base
    width: 200
    property string name
    property string description
    property string formattedText
    height: 40

    background: RectangularShadow {
        width: parent.width
        height: parent.height

        offset.x: 0
        offset.y: 0
        radius: 0
        blur: 30
        spread: 10
        color: "white"
    }

    RuleNodeHintModel {
        id: hintModel
    }

    function showHint(ruleName)
    {
        visible = true;
        hintModel.setHint(ruleName);
        updateData();
    }

    property var fontSize: 20

        function updateName()
        {
            titleREAD.text = hintModel.getName();
        }
        function updateDesc()
        {
            descREAD.text = hintModel.getFormattedText();
        }
        function updateData()
        {
            base.width = base.parent.width;
            updateName();
            updateDesc();
            setWidth();
            setNewHeight();
        }

        function setWidth()
        {
            base.width = Math.min(Math.max(titleREAD.implicitWidth + 30, 200), base.parent.width);
        }

        function setNewHeight()
        {
            var titleHeight = titleREAD.contentHeight + titleUnderLine.height;
            descBackground.height = descREAD.height;

            base.height = descBackground.height + titleHeight + column.padding + 5;/*bottom margin*/
            bG.height = base.height
        }

        Component.onCompleted: {
            updateData();
            setNewHeight();
        }

        Rectangle {
            height: parent.height
            width: parent.width
            color: "black"
            id: bG

            //name: "Test"
            Column {
                id: column
                anchors.fill: parent

                RowLayout {
                    width: parent.width

                    Text {
                        id: titleREAD
                        text: base.name
                        wrapMode: Text.Wrap
                        color: "white"
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignBottom
                        Layout.leftMargin: 5
                        font.pointSize: base.fontSize
                        font.bold: true
                    }
                }


                Rectangle {
                    id: titleUnderLine
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 2
                    width: parent.width - 10

                    color: "yellow"
                }
                Rectangle {
                    id: descBackground
                    anchors.topMargin: 5
                    width: parent.width - 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "gray"
                    Text {
                        id: descREAD
                        textFormat: Text.MarkdownText
                        text: base.formattedText
                        width: parent.width
                        wrapMode: Text.Wrap
                        color: "black"
                        onWidthChanged: {
                            base.setNewHeight();
                        }
                        Component.onCompleted: {
                            base.setNewHeight();
                        }
                        font.pointSize: base.fontSize

                    }


                }
            }
        }
    }
