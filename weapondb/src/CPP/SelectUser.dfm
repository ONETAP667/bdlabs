object SelectUserForm: TSelectUserForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Select Byer'
  ClientHeight = 425
  ClientWidth = 305
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object lbl1: TLabel
    Left = 8
    Top = 10
    Width = 76
    Height = 13
    Caption = 'User to sell item'
  end
  object btnOk: TButton
    Left = 223
    Top = 33
    Width = 75
    Height = 25
    Caption = 'Ok'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object btn1: TButton
    Left = 223
    Top = 64
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object ud1: TUpDown
    Left = 106
    Top = 387
    Width = 16
    Height = 21
    Associate = lbledt2
    Max = 10000000
    Increment = 10
    TabOrder = 2
  end
  object lbledt2: TLabeledEdit
    Left = 8
    Top = 387
    Width = 98
    Height = 21
    EditLabel.Width = 38
    EditLabel.Height = 13
    EditLabel.Caption = 'By price'
    TabOrder = 3
    Text = '0'
  end
  object dblklst1: TDBLookupListBox
    Left = 8
    Top = 29
    Width = 193
    Height = 329
    TabOrder = 4
  end
end
