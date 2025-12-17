object EditUserForm: TEditUserForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'User Parasmeters'
  ClientHeight = 125
  ClientWidth = 320
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object lbledt1: TLabeledEdit
    Left = 16
    Top = 24
    Width = 177
    Height = 21
    EditLabel.Width = 52
    EditLabel.Height = 13
    EditLabel.Caption = 'User Name'
    TabOrder = 0
    OnChange = lbledt1Change
  end
  object lbledt2: TLabeledEdit
    Left = 16
    Top = 65
    Width = 154
    Height = 21
    EditLabel.Width = 37
    EditLabel.Height = 13
    EditLabel.Caption = 'Balance'
    TabOrder = 1
    Text = '0'
  end
  object ud1: TUpDown
    Left = 170
    Top = 65
    Width = 16
    Height = 21
    Associate = lbledt2
    Max = 10000000
    Increment = 10
    TabOrder = 2
  end
  object btn1: TButton
    Left = 224
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Ok'
    Default = True
    Enabled = False
    ModalResult = 1
    TabOrder = 3
  end
  object btn2: TButton
    Left = 224
    Top = 63
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 4
  end
end
