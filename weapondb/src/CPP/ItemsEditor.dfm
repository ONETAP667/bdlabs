object ItemEditForm: TItemEditForm
  Left = 0
  Top = 0
  Caption = 'ItemEditForm'
  ClientHeight = 333
  ClientWidth = 638
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  DesignSize = (
    638
    333)
  PixelsPerInch = 96
  TextHeight = 13
  object lbl1: TLabel
    Left = 8
    Top = 6
    Width = 24
    Height = 13
    Caption = 'Type'
  end
  object lbl2: TLabel
    Left = 176
    Top = 6
    Width = 40
    Height = 13
    Caption = 'Weapon'
    FocusControl = dblklst1
  end
  object lbl211: TLabel
    Left = 12
    Top = 108
    Width = 20
    Height = 13
    Caption = 'Kind'
    FocusControl = dblklstSpecialDescription
  end
  object img1: TImage
    Left = 343
    Top = 112
    Width = 162
    Height = 164
    AutoSize = True
    Stretch = True
  end
  object lbl3: TLabel
    Left = 343
    Top = 93
    Width = 38
    Height = 13
    Caption = 'Preview'
  end
  object btn1: TButton
    Left = 474
    Top = 300
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Ok'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object btn2: TButton
    Left = 555
    Top = 300
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object lbledt2: TLabeledEdit
    Left = 343
    Top = 66
    Width = 140
    Height = 21
    EditLabel.Width = 23
    EditLabel.Height = 13
    EditLabel.Caption = 'Price'
    TabOrder = 2
    Text = '10'
  end
  object ud1: TUpDown
    Left = 483
    Top = 66
    Width = 16
    Height = 21
    Associate = lbledt2
    Max = 10000000
    Increment = 10
    Position = 10
    TabOrder = 3
  end
  object lbledt3: TLabeledEdit
    Left = 343
    Top = 25
    Width = 281
    Height = 21
    EditLabel.Width = 45
    EditLabel.Height = 13
    EditLabel.Caption = 'NameTag'
    TabOrder = 4
  end
  object dblklst1: TDBLookupListBox
    Left = 176
    Top = 25
    Width = 153
    Height = 251
    KeyField = 'WeaponID'
    ListField = 'Weapon'
    TabOrder = 5
  end
  object dblklstSpecialDescription: TDBLookupListBox
    Left = 8
    Top = 129
    Width = 153
    Height = 147
    BevelInner = bvNone
    BevelOuter = bvNone
    KeyField = 'SpecialID'
    ListField = 'Category'
    TabOrder = 6
  end
  object dblklstItemDescription: TDBLookupListBox
    Left = 8
    Top = 25
    Width = 153
    Height = 69
    TabOrder = 7
    OnClick = dblklstItemDescriptionClick
  end
  object btn3: TButton
    Left = 549
    Top = 112
    Width = 75
    Height = 25
    Caption = 'Load'
    TabOrder = 8
    OnClick = btn3Click
  end
  object dlgOpenPic1: TOpenPictureDialog
    Left = 528
    Top = 192
  end
end
