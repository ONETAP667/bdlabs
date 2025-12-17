object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Form2'
  ClientHeight = 292
  ClientWidth = 638
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    638
    292)
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
  object btn1: TButton
    Left = 474
    Top = 259
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Ok'
    Default = True
    ModalResult = 1
    TabOrder = 0
    ExplicitLeft = 471
    ExplicitTop = 237
  end
  object btn2: TButton
    Left = 555
    Top = 259
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
    ExplicitLeft = 552
    ExplicitTop = 237
  end
  object lbledt2: TLabeledEdit
    Left = 343
    Top = 129
    Width = 98
    Height = 21
    EditLabel.Width = 23
    EditLabel.Height = 13
    EditLabel.Caption = 'Price'
    TabOrder = 2
    Text = '0'
  end
  object ud1: TUpDown
    Left = 441
    Top = 129
    Width = 16
    Height = 21
    Associate = lbledt2
    Max = 10000000
    Increment = 10
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
  object dblklstItemDescription: TDBLookupListBox
    Left = 8
    Top = 25
    Width = 153
    Height = 69
    DataField = 'ItemDescription'
    KeyField = 'TypeID'
    ListField = 'Description'
    ReadOnly = True
    TabOrder = 5
    OnClick = dblklstItemDescriptionClick
  end
  object lbledt4: TLabeledEdit
    Left = 343
    Top = 79
    Width = 281
    Height = 21
    EditLabel.Width = 38
    EditLabel.Height = 13
    EditLabel.Caption = 'Preview'
    TabOrder = 6
  end
  object dblklst1: TDBLookupListBox
    Left = 176
    Top = 25
    Width = 153
    Height = 251
    DataField = 'WeaponDescription'
    KeyField = 'WeaponID'
    ListField = 'Weapon'
    TabOrder = 7
  end
  object dblklstSpecialDescription: TDBLookupListBox
    Left = 8
    Top = 129
    Width = 153
    Height = 147
    DataField = 'SpecialDescription'
    KeyField = 'SpecialID'
    ListField = 'Category'
    TabOrder = 8
  end
end
