object SelWeaponsForm: TSelWeaponsForm
  Left = 0
  Top = 0
  Caption = 'Select Weapons'
  ClientHeight = 386
  ClientWidth = 351
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object dblklst1: TDBLookupListBox
    Left = 8
    Top = 8
    Width = 225
    Height = 368
    KeyField = 'ID'
    ListField = 'Nametag '
    ListSource = ds1
    TabOrder = 0
  end
  object btn1: TButton
    Left = 256
    Top = 24
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object btn2: TButton
    Left = 256
    Top = 64
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
  object fdqry1: TFDQuery
    Connection = MainForm.con1
    Transaction = MainForm.fdtrans1
    SQL.Strings = (
      '')
    Left = 128
    Top = 168
  end
  object ds1: TDataSource
    DataSet = fdqry1
    Left = 96
    Top = 216
  end
end
