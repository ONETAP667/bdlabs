object DashBoardForm: TDashBoardForm
  Left = 0
  Top = 0
  Caption = 'Dashboard'
  ClientHeight = 548
  ClientWidth = 1145
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object pgc1: TPageControl
    Left = 2
    Top = 0
    Width = 1143
    Height = 548
    ActivePage = ts1
    Align = alRight
    TabOrder = 0
    object ts1: TTabSheet
      Caption = 'Statistics'
      object pnl3: TPanel
        Left = 895
        Top = 0
        Width = 240
        Height = 520
        Align = alRight
        BevelOuter = bvNone
        TabOrder = 0
        DesignSize = (
          240
          520)
        object btnRefresh: TButton
          Left = 151
          Top = 495
          Width = 75
          Height = 25
          Anchors = [akTop, akRight]
          Caption = 'Load'
          TabOrder = 0
          OnClick = btnRefreshClick
        end
        object grp1: TGroupBox
          Left = 14
          Top = 10
          Width = 219
          Height = 477
          Caption = 'Filters'
          TabOrder = 1
          object cbUser: TComboBox
            Left = 14
            Top = 39
            Width = 190
            Height = 21
            DropDownCount = 10
            Sorted = True
            TabOrder = 0
          end
          object chk1: TCheckBox
            Left = 16
            Top = 16
            Width = 97
            Height = 17
            Caption = 'By user'
            TabOrder = 1
            OnClick = chk1Click
          end
          object grp2: TGroupBox
            Left = 6
            Top = 76
            Width = 205
            Height = 131
            TabOrder = 2
            object lbl2: TLabel
              Left = 8
              Top = 17
              Width = 46
              Height = 13
              Caption = 'Date Fom'
            end
            object lbl3: TLabel
              Left = 8
              Top = 67
              Width = 38
              Height = 13
              Caption = 'Date To'
              FocusControl = dpTo
            end
            object dpFrom: TDateTimePicker
              Left = 8
              Top = 34
              Width = 190
              Height = 21
              Date = 46001.000000000000000000
              Time = 0.736376203705731300
              TabOrder = 0
            end
            object dpTo: TDateTimePicker
              Left = 8
              Top = 84
              Width = 190
              Height = 21
              Date = 46001.000000000000000000
              Time = 0.736376203705731300
              TabOrder = 1
            end
          end
          object chk2: TCheckBox
            Left = 16
            Top = 66
            Width = 61
            Height = 17
            Caption = 'By date'
            TabOrder = 3
            OnClick = chk2Click
          end
        end
      end
      object pnl1: TPanel
        Left = 0
        Top = 0
        Width = 895
        Height = 520
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 1
        object lblMarket: TLabel
          Left = 0
          Top = 0
          Width = 895
          Height = 37
          Align = alTop
          Alignment = taCenter
          AutoSize = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          ExplicitWidth = 894
        end
        object spl1: TSplitter
          Left = 0
          Top = 273
          Width = 895
          Height = 3
          Cursor = crVSplit
          Align = alTop
          ExplicitTop = 249
          ExplicitWidth = 204
        end
        object dbgrdUsers: TDBGrid
          Left = 0
          Top = 37
          Width = 895
          Height = 236
          Align = alTop
          DataSource = dsUsers
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
          ReadOnly = True
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
          Columns = <
            item
              Expanded = False
              FieldName = 'Username'
              Title.Caption = 'User name'
              Width = 400
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'items_count'
              Title.Caption = 'Items count'
              Width = 200
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'total_value'
              Title.Caption = 'Total cost'
              Width = 200
              Visible = True
            end>
        end
        object pnl: TPanel
          Left = 0
          Top = 276
          Width = 895
          Height = 244
          Align = alClient
          BevelOuter = bvNone
          TabOrder = 1
          object pnl2: TPanel
            Left = 0
            Top = 0
            Width = 895
            Height = 244
            Align = alClient
            BevelOuter = bvLowered
            TabOrder = 0
            object chtDeals: TChart
              Left = 1
              Top = 1
              Width = 893
              Height = 242
              Title.Font.Color = 8404992
              Title.Text.Strings = (
                'TChart')
              View3D = False
              Align = alClient
              TabOrder = 0
              DefaultCanvas = 'TGDIPlusCanvas'
              ColorPaletteIndex = 13
              object Series1: TFastLineSeries
                LinePen.Color = 10708548
                XValues.Name = 'X'
                XValues.Order = loAscending
                YValues.Name = 'Y'
                YValues.Order = loNone
              end
            end
          end
        end
      end
    end
    object ts2: TTabSheet
      Caption = 'Price trend'
      ImageIndex = 1
      object pnl4: TPanel
        Left = 0
        Top = 0
        Width = 895
        Height = 520
        Align = alClient
        TabOrder = 0
        object dbgTrend: TDBGrid
          Left = 1
          Top = 1
          Width = 893
          Height = 518
          Align = alClient
          DataSource = dsPriceTrend
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
          ReadOnly = True
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
          Columns = <
            item
              Expanded = False
              FieldName = 'ID'
              Visible = False
            end
            item
              Expanded = False
              FieldName = 'Nametag'
              Title.Caption = 'Name'
              Width = 200
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'first_price'
              Title.Caption = 'First price'
              Width = 100
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'last_price'
              Title.Caption = 'Last Price'
              Width = 100
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'avg_price'
              Title.Caption = 'Average price'
              Width = 100
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'price_change'
              Title.Caption = 'Price change'
              Width = 100
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'change_percent'
              Title.Caption = 'Change %'
              Width = 100
              Visible = True
            end>
        end
      end
      object pnl31: TPanel
        Left = 895
        Top = 0
        Width = 240
        Height = 520
        Align = alRight
        BevelOuter = bvNone
        TabOrder = 1
        DesignSize = (
          240
          520)
        object btnRefresh1: TButton
          Left = 151
          Top = 495
          Width = 75
          Height = 25
          Anchors = [akTop, akRight]
          Caption = 'Load'
          TabOrder = 0
          OnClick = btnRefresh1Click
        end
        object grp11: TGroupBox
          Left = 10
          Top = 10
          Width = 219
          Height = 477
          Caption = 'Filters'
          TabOrder = 1
          object lbl1: TLabel
            Left = 18
            Top = 67
            Width = 47
            Height = 13
            Caption = 'Item type'
            FocusControl = cbType
          end
          object lbl11: TLabel
            Left = 18
            Top = 115
            Width = 40
            Height = 13
            Caption = 'Weapon'
            FocusControl = cbWeapon
          end
          object lbl111: TLabel
            Left = 18
            Top = 165
            Width = 20
            Height = 13
            Caption = 'Kind'
            FocusControl = cbSpecial
          end
          object cbType: TComboBox
            Left = 14
            Top = 84
            Width = 190
            Height = 22
            Style = csOwnerDrawFixed
            DropDownCount = 10
            TabOrder = 0
            OnChange = cbTypeChange
          end
          object edSearch: TLabeledEdit
            Left = 14
            Top = 34
            Width = 190
            Height = 21
            EditLabel.Width = 51
            EditLabel.Height = 13
            EditLabel.Caption = 'Item name'
            TabOrder = 1
          end
          object cbWeapon: TComboBox
            Left = 14
            Top = 132
            Width = 190
            Height = 22
            Style = csOwnerDrawFixed
            DropDownCount = 10
            TabOrder = 2
            OnChange = cbTypeChange
          end
          object cbSpecial: TComboBox
            Left = 14
            Top = 182
            Width = 190
            Height = 22
            Style = csOwnerDrawFixed
            DropDownCount = 10
            TabOrder = 3
            OnChange = cbTypeChange
          end
          object cbOrder: TRadioGroup
            Left = 14
            Top = 226
            Width = 190
            Height = 125
            Caption = 'Order by'
            ItemIndex = 0
            Items.Strings = (
              'Price increase'#10
              'Price decrease'#10
              'High average price'
              #10'Low average price'#10
              'Item name A-Z')
            TabOrder = 4
            OnClick = cbTypeChange
          end
          object chk3: TCheckBox
            Left = 146
            Top = 452
            Width = 67
            Height = 17
            Caption = 'Auto Lolad'
            Checked = True
            State = cbChecked
            TabOrder = 5
          end
        end
      end
    end
  end
  object qMarket: TFDQuery
    BeforeOpen = qMarketBeforeOpen
    Connection = MainForm.con1
    Left = 114
    Top = 68
  end
  object qUsers: TFDQuery
    BeforeOpen = qMarketBeforeOpen
    Connection = MainForm.con1
    Left = 220
    Top = 58
  end
  object qDeals: TFDQuery
    BeforeOpen = qMarketBeforeOpen
    Connection = MainForm.con1
    Left = 364
    Top = 78
  end
  object dsUsers: TDataSource
    DataSet = qUsers
    Left = 234
    Top = 154
  end
  object dsDeals: TDataSource
    DataSet = qDeals
    Left = 348
    Top = 180
  end
  object fdqrySvc: TFDQuery
    BeforeOpen = qMarketBeforeOpen
    Connection = MainForm.con1
    Left = 502
    Top = 112
  end
  object qPriceTrend: TFDQuery
    BeforeOpen = qMarketBeforeOpen
    Connection = MainForm.con1
    Left = 240
    Top = 376
  end
  object dsPriceTrend: TDataSource
    DataSet = qPriceTrend
    Left = 370
    Top = 372
  end
end
