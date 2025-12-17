object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'MainForm'
  ClientHeight = 535
  ClientWidth = 1231
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = mm1
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object spl1: TSplitter
    Left = 0
    Top = 369
    Width = 1231
    Height = 3
    Cursor = crVSplit
    Align = alTop
    ExplicitTop = 193
    ExplicitWidth = 323
  end
  object pgc1: TPageControl
    Left = 0
    Top = 0
    Width = 1231
    Height = 369
    ActivePage = ts1
    Align = alTop
    TabOrder = 0
    OnChange = pgc1Change
    object ts1: TTabSheet
      Caption = 'Users'
      ImageIndex = 2
      object pnl5: TPanel
        Left = 0
        Top = 0
        Width = 1223
        Height = 169
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object spl4: TSplitter
          Left = 757
          Top = 0
          Height = 169
          Align = alRight
          ExplicitLeft = 755
        end
        object pnl6: TPanel
          Left = 0
          Top = 0
          Width = 757
          Height = 169
          Align = alClient
          TabOrder = 0
          object pnl3: TPanel
            Left = 1
            Top = 1
            Width = 755
            Height = 24
            Align = alTop
            BevelOuter = bvNone
            TabOrder = 0
            object lbl1: TLabel
              Left = 5
              Top = 5
              Width = 27
              Height = 13
              Caption = 'Users'
            end
          end
          object dbgrd1: TDBGrid
            Left = 1
            Top = 25
            Width = 755
            Height = 143
            Align = alClient
            DataSource = dsUsers
            PopupMenu = pm1
            TabOrder = 1
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
                FieldName = 'Username'
                Width = 200
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'Balance'
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'DateJoined'
                Title.Alignment = taRightJustify
                Width = 120
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'Restriction'
                Width = 120
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'RestrictedUntil'
                Width = 120
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'Archive'
                Title.Caption = 'Archived'
                Width = 80
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'Version'
                Visible = False
              end>
          end
        end
        object pnl7: TPanel
          Left = 760
          Top = 0
          Width = 463
          Height = 169
          Align = alRight
          BevelOuter = bvNone
          TabOrder = 1
          DesignSize = (
            463
            169)
          object lbl9: TLabel
            Left = 12
            Top = 12
            Width = 75
            Height = 13
            Caption = 'Username mask'
            FocusControl = edtUserMask
          end
          object chkJoinedFrom: TCheckBox
            Left = 195
            Top = 5
            Width = 97
            Height = 17
            Caption = 'Joined from'
            TabOrder = 0
            OnClick = chkJoinedFromClick
          end
          object chkJoinedTo: TCheckBox
            Left = 334
            Top = 5
            Width = 97
            Height = 17
            Caption = 'Joined to'
            TabOrder = 1
            OnClick = chkJoinedToClick
          end
          object dtJoinedTo: TDateTimePicker
            Left = 334
            Top = 30
            Width = 120
            Height = 21
            Date = 46000.000000000000000000
            Time = 0.803206643518933600
            Enabled = False
            TabOrder = 2
          end
          object dtJoinedFrom: TDateTimePicker
            Left = 195
            Top = 30
            Width = 120
            Height = 21
            Date = 46000.000000000000000000
            Time = 0.803206643518933600
            Enabled = False
            TabOrder = 3
          end
          object grp31: TGroupBox
            Left = 195
            Top = 63
            Width = 145
            Height = 83
            Caption = 'Balance'
            TabOrder = 4
            object lbl511: TLabel
              Left = 6
              Top = 52
              Width = 12
              Height = 13
              Caption = 'To'
            end
            object lbl52: TLabel
              Left = 6
              Top = 20
              Width = 24
              Height = 13
              Caption = 'From'
            end
            object edt12: TEdit
              Left = 48
              Top = 18
              Width = 73
              Height = 21
              TabOrder = 0
              Text = '0'
            end
            object udBalanceFrom: TUpDown
              Left = 121
              Top = 18
              Width = 16
              Height = 21
              Associate = edt12
              TabOrder = 1
            end
            object udBalanceTo: TUpDown
              Left = 121
              Top = 49
              Width = 16
              Height = 21
              Associate = edt111
              TabOrder = 2
            end
            object edt111: TEdit
              Left = 48
              Top = 49
              Width = 73
              Height = 21
              TabOrder = 3
              Text = '0'
            end
          end
          object edtUserMask: TEdit
            Left = 11
            Top = 30
            Width = 171
            Height = 21
            TabOrder = 5
          end
          object grpState: TGroupBox
            Left = 11
            Top = 63
            Width = 171
            Height = 83
            Caption = 'State'
            TabOrder = 6
            object chkInactive: TCheckBox
              Left = 9
              Top = 51
              Width = 97
              Height = 17
              Caption = 'In archive'
              TabOrder = 0
            end
            object chkResreicted: TCheckBox
              Left = 9
              Top = 20
              Width = 97
              Height = 17
              Caption = 'Restricted'
              TabOrder = 1
            end
          end
          object btnFilterUsers: TButton
            Left = 379
            Top = 83
            Width = 75
            Height = 25
            Anchors = [akRight, akBottom]
            Caption = 'Filter'
            TabOrder = 7
            OnClick = btnFilterUsersClick
          end
          object btnAllUsers: TButton
            Left = 380
            Top = 121
            Width = 75
            Height = 25
            Anchors = [akRight, akBottom]
            Caption = 'Reset'
            TabOrder = 8
            OnClick = btnAllUsersClick
          end
        end
      end
      object pnl8: TPanel
        Left = 0
        Top = 169
        Width = 1223
        Height = 172
        Align = alClient
        TabOrder = 1
        object spl6: TSplitter
          Left = 754
          Top = 1
          Height = 170
          ExplicitLeft = 762
          ExplicitTop = 0
        end
        object pnl9: TPanel
          Left = 1
          Top = 1
          Width = 753
          Height = 170
          Align = alLeft
          BevelOuter = bvNone
          TabOrder = 0
          object lbl3: TLabel
            Left = 0
            Top = 0
            Width = 753
            Height = 13
            Align = alTop
            Caption = 'Items'
            ExplicitWidth = 27
          end
          object dbgrd2: TDBGrid
            Left = 0
            Top = 13
            Width = 753
            Height = 157
            Align = alClient
            DataSource = dsUserItems
            PopupMenu = pm4
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
                Width = 50
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'OwnerID'
                Visible = False
              end
              item
                Expanded = False
                FieldName = 'Nametag'
                Title.Caption = 'Name'
                Width = 150
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'WeaponDescription'
                Title.Caption = 'Weapon'
                Width = 200
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'ItemDescription'
                Title.Caption = 'Type'
                Width = 100
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'Price'
                Title.Alignment = taRightJustify
                Width = 100
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'SpecialDescription'
                Title.Caption = 'Special'
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'Type'
                Title.Caption = 'aType'
                Visible = False
              end
              item
                Expanded = False
                FieldName = 'Preview'
                Visible = False
              end>
          end
        end
        object pnl10: TPanel
          Left = 757
          Top = 1
          Width = 465
          Height = 170
          Align = alClient
          BevelOuter = bvNone
          TabOrder = 1
          object lbl4: TLabel
            Left = 0
            Top = 0
            Width = 465
            Height = 13
            Align = alTop
            Caption = 'Weapon'#39's Items'
            ExplicitWidth = 77
          end
          object dbgrd3: TDBGrid
            Left = 0
            Top = 13
            Width = 465
            Height = 157
            Align = alClient
            DataSource = dsStikers
            TabOrder = 0
            TitleFont.Charset = DEFAULT_CHARSET
            TitleFont.Color = clWindowText
            TitleFont.Height = -11
            TitleFont.Name = 'Tahoma'
            TitleFont.Style = []
            Columns = <
              item
                Expanded = False
                FieldName = 'ItemID'
                Title.Caption = 'Weapon ID'
                Width = 65
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'Nametag'
                Title.Caption = 'Name'
                Width = 150
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'Price'
                Title.Alignment = taRightJustify
                Width = 100
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'ItemDescription'
                Title.Caption = 'Type'
                Width = 100
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'SpecialDescription'
                Title.Caption = 'Kind'
                Width = 100
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'ID'
                Visible = False
              end>
          end
        end
      end
    end
    object ts2: TTabSheet
      Caption = 'Items'
      ImageIndex = 1
      object pnl1: TPanel
        Left = 0
        Top = 0
        Width = 882
        Height = 341
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object dbgrdItemsTable: TDBGrid
          Left = 0
          Top = 0
          Width = 882
          Height = 341
          Align = alClient
          DataSource = dsItems
          PopupMenu = pm2
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
              Width = 50
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'Owner'
              Width = 120
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'Nametag'
              Title.Caption = 'Name'
              Width = 150
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'Price'
              Title.Alignment = taRightJustify
              Width = 100
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'ItemDescription'
              Title.Caption = 'Type'
              Width = 100
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'WeaponDescription'
              Title.Caption = 'Weapon'
              Width = 200
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'SpecialDescription'
              Title.Caption = 'Special'
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'OwnerID'
              Visible = False
            end
            item
              Expanded = False
              FieldName = 'Preview'
              Visible = False
            end
            item
              Expanded = False
              FieldName = 'Type'
              Visible = False
            end>
        end
      end
      object pnl17: TPanel
        Left = 882
        Top = 0
        Width = 341
        Height = 341
        Align = alRight
        TabOrder = 1
        DesignSize = (
          341
          341)
        object lbl8: TLabel
          Left = 178
          Top = 124
          Width = 49
          Height = 13
          Caption = 'Owned by'
          FocusControl = edtItemOwnerMask
        end
        object grp3: TGroupBox
          Left = 11
          Top = 119
          Width = 150
          Height = 86
          TabOrder = 7
          object lbl51: TLabel
            Left = 4
            Top = 57
            Width = 12
            Height = 13
            Caption = 'To'
          end
          object lbl5: TLabel
            Left = 4
            Top = 25
            Width = 24
            Height = 13
            Caption = 'From'
          end
          object edt1: TEdit
            Left = 48
            Top = 23
            Width = 73
            Height = 21
            TabOrder = 0
            Text = '0'
          end
          object udItemPriceFrom: TUpDown
            Left = 121
            Top = 23
            Width = 16
            Height = 21
            Associate = edt1
            TabOrder = 1
          end
          object udItemPriceTo: TUpDown
            Left = 121
            Top = 54
            Width = 16
            Height = 21
            Associate = edt11
            TabOrder = 2
          end
          object edt11: TEdit
            Left = 48
            Top = 54
            Width = 73
            Height = 21
            TabOrder = 3
            Text = '0'
          end
        end
        object dtAddedFrom: TDateTimePicker
          Left = 178
          Top = 24
          Width = 153
          Height = 21
          Date = 46000.000000000000000000
          Time = 0.803206643518933600
          Enabled = False
          TabOrder = 0
        end
        object btnAllItems: TButton
          Left = 259
          Top = 302
          Width = 75
          Height = 25
          Anchors = [akRight, akBottom]
          Caption = 'Reset'
          TabOrder = 1
          OnClick = btnAllItemsClick
        end
        object edtItemOwnerMask: TEdit
          Left = 178
          Top = 143
          Width = 153
          Height = 21
          TabOrder = 2
        end
        object dtAddedTo: TDateTimePicker
          Left = 178
          Top = 76
          Width = 153
          Height = 21
          Date = 46000.000000000000000000
          Time = 0.803206643518933600
          Enabled = False
          TabOrder = 3
        end
        object chkAddeTo: TCheckBox
          Left = 178
          Top = 54
          Width = 97
          Height = 17
          Caption = 'Added to'
          TabOrder = 4
          OnClick = chkAddeToClick
        end
        object chkAddeFrom: TCheckBox
          Left = 178
          Top = 4
          Width = 97
          Height = 17
          Caption = 'Added from'
          TabOrder = 5
          OnClick = chkAddeFromClick
        end
        object chkPrice: TCheckBox
          Left = 19
          Top = 114
          Width = 56
          Height = 16
          Caption = 'Price'
          TabOrder = 6
          OnClick = chkPriceClick
        end
        object grp2: TGroupBox
          Left = 11
          Top = 1
          Width = 150
          Height = 101
          Caption = 'Type'
          TabOrder = 8
          object chkWP: TCheckBox
            Left = 8
            Top = 14
            Width = 97
            Height = 17
            Caption = 'Weapon'
            TabOrder = 0
          end
          object chkStk: TCheckBox
            Left = 8
            Top = 35
            Width = 97
            Height = 17
            Caption = 'Sticker'
            TabOrder = 1
          end
          object chkContainer: TCheckBox
            Left = 8
            Top = 57
            Width = 97
            Height = 17
            Caption = 'Container'
            TabOrder = 2
          end
          object chkKeychain: TCheckBox
            Left = 8
            Top = 78
            Width = 97
            Height = 17
            Caption = 'Keychain'
            TabOrder = 3
          end
        end
        object btnFilterItems: TButton
          Left = 259
          Top = 264
          Width = 75
          Height = 25
          Anchors = [akRight, akBottom]
          Caption = 'Filter'
          TabOrder = 9
          OnClick = btnFilterItemsClick
        end
      end
    end
    object ts3: TTabSheet
      Caption = 'Transactions'
      ImageIndex = 3
      object pnl13: TPanel
        Left = 0
        Top = 0
        Width = 914
        Height = 341
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object dbgrdTransactions: TDBGrid
          Left = 0
          Top = 0
          Width = 914
          Height = 341
          Align = alClient
          DataSource = dsTransaction
          PopupMenu = pm3
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
          Columns = <
            item
              Expanded = False
              FieldName = 'TransactionID'
              Visible = False
            end
            item
              Expanded = False
              FieldName = 'SellerID'
              Visible = False
            end
            item
              Expanded = False
              FieldName = 'BuyerID'
              Visible = False
            end
            item
              Expanded = False
              FieldName = 'ItemID'
              Visible = False
            end
            item
              Expanded = False
              FieldName = 'SellerName'
              Title.Caption = 'Seller'
              Width = 180
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'BuyerName'
              Title.Caption = 'Buyer'
              Width = 180
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'ItemNametag'
              Title.Caption = 'Item'
              Width = 180
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'Price'
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'Date'
              Width = 95
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'ItemType'
              Title.Caption = 'Type'
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'Archive'
              Title.Caption = 'Archived'
              Width = 55
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'Canceled'
              Title.Caption = 'Cancelled'
              Width = 55
              Visible = True
            end>
        end
      end
      object pnl16: TPanel
        Left = 914
        Top = 0
        Width = 309
        Height = 341
        Align = alRight
        BevelOuter = bvNone
        TabOrder = 1
        DesignSize = (
          309
          341)
        object Seller: TLabel
          Left = 10
          Top = 8
          Width = 58
          Height = 13
          Caption = 'Sellers mask'
          FocusControl = edtSeller
        end
        object lbl6: TLabel
          Left = 86
          Top = 59
          Width = 3
          Height = 13
          FocusControl = edtByer
        end
        object lbl7: TLabel
          Left = 10
          Top = 64
          Width = 57
          Height = 13
          Caption = 'Byers  mask'
        end
        object lbl71: TLabel
          Left = 10
          Top = 115
          Width = 54
          Height = 13
          Caption = 'Items mask'
        end
        object btnFilterTransactions: TButton
          Left = 228
          Top = 265
          Width = 75
          Height = 25
          Anchors = [akRight, akBottom]
          Caption = 'Filter'
          TabOrder = 0
          OnClick = btnFilterTransactionsClick
        end
        object btnAllTransactions: TButton
          Left = 229
          Top = 300
          Width = 75
          Height = 25
          Anchors = [akRight, akBottom]
          Caption = 'Reset'
          TabOrder = 1
          OnClick = btnAllTransactionsClick
        end
        object dtTrarnsFrom: TDateTimePicker
          Left = 163
          Top = 28
          Width = 139
          Height = 21
          Date = 46000.000000000000000000
          Time = 0.803206643518933600
          Enabled = False
          TabOrder = 2
        end
        object grp311: TGroupBox
          Left = 10
          Top = 163
          Width = 140
          Height = 83
          Caption = 'Price'
          TabOrder = 3
          object lbl5111: TLabel
            Left = 6
            Top = 52
            Width = 12
            Height = 13
            Caption = 'To'
          end
          object lbl521: TLabel
            Left = 6
            Top = 20
            Width = 24
            Height = 13
            Caption = 'From'
          end
          object edt121: TEdit
            Left = 44
            Top = 18
            Width = 73
            Height = 21
            TabOrder = 0
            Text = '0'
          end
          object udPriceFrom: TUpDown
            Left = 117
            Top = 18
            Width = 16
            Height = 21
            Associate = edt121
            TabOrder = 1
          end
          object udPriceTo: TUpDown
            Left = 117
            Top = 49
            Width = 16
            Height = 21
            Associate = edt1111
            TabOrder = 2
          end
          object edt1111: TEdit
            Left = 44
            Top = 49
            Width = 73
            Height = 21
            TabOrder = 3
            Text = '0'
          end
        end
        object grpState1: TGroupBox
          Left = 164
          Top = 163
          Width = 140
          Height = 83
          Caption = 'State'
          TabOrder = 4
          object chkTransArchived: TCheckBox
            Left = 15
            Top = 20
            Width = 97
            Height = 17
            Caption = 'In archive'
            TabOrder = 0
          end
          object chkTransCancelled: TCheckBox
            Left = 15
            Top = 49
            Width = 97
            Height = 17
            Caption = 'Canceled'
            TabOrder = 1
          end
        end
        object chkTrDateFrom: TCheckBox
          Left = 163
          Top = 7
          Width = 97
          Height = 17
          Caption = 'Date from'
          TabOrder = 5
          OnClick = chkJoinedFromClick
        end
        object dtTrarnsTo: TDateTimePicker
          Left = 163
          Top = 79
          Width = 139
          Height = 21
          Date = 46000.000000000000000000
          Time = 0.803206643518933600
          Enabled = False
          TabOrder = 6
        end
        object edtSeller: TEdit
          Left = 10
          Top = 28
          Width = 140
          Height = 21
          TabOrder = 7
        end
        object chkTrDateTo: TCheckBox
          Left = 163
          Top = 58
          Width = 97
          Height = 17
          Caption = 'Date to'
          TabOrder = 8
          OnClick = chkJoinedToClick
        end
        object edtByer: TEdit
          Left = 10
          Top = 79
          Width = 140
          Height = 21
          TabOrder = 9
        end
        object edtItems: TEdit
          Left = 10
          Top = 130
          Width = 140
          Height = 21
          TabOrder = 10
        end
      end
    end
    object stuff: TTabSheet
      Caption = 'Lookups and options'
      ImageIndex = 2
      object pnl11: TPanel
        Left = 0
        Top = 0
        Width = 320
        Height = 341
        Align = alLeft
        BevelKind = bkFlat
        BevelOuter = bvNone
        TabOrder = 0
        object pnl42: TPanel
          Left = 0
          Top = 0
          Width = 316
          Height = 25
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Weapons'
          TabOrder = 0
          object dbnvgr22: TDBNavigator
            Left = 76
            Top = 0
            Width = 240
            Height = 25
            DataSource = dsWeaponID
            Align = alRight
            TabOrder = 0
          end
        end
        object dbgrd42: TDBGrid
          Left = 0
          Top = 25
          Width = 316
          Height = 312
          Align = alClient
          DataSource = dsWeaponID
          TabOrder = 1
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
        end
      end
      object pnl12: TPanel
        Left = 320
        Top = 0
        Width = 330
        Height = 341
        Align = alLeft
        TabOrder = 1
        object spl2: TSplitter
          Left = 1
          Top = 169
          Width = 328
          Height = 3
          Cursor = crVSplit
          Align = alTop
          ExplicitWidth = 171
        end
        object pnl: TPanel
          Left = 1
          Top = 1
          Width = 328
          Height = 168
          Align = alTop
          BevelKind = bkFlat
          BevelOuter = bvNone
          TabOrder = 0
          object pnl41: TPanel
            Left = 0
            Top = 0
            Width = 324
            Height = 25
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = ' Type'
            TabOrder = 0
            object dbnvgr21: TDBNavigator
              Left = 84
              Top = 0
              Width = 240
              Height = 25
              DataSource = dsItemTypes
              Align = alRight
              TabOrder = 0
            end
          end
          object dbgrd41: TDBGrid
            Left = 0
            Top = 25
            Width = 324
            Height = 139
            Align = alClient
            DataSource = dsItemTypes
            TabOrder = 1
            TitleFont.Charset = DEFAULT_CHARSET
            TitleFont.Color = clWindowText
            TitleFont.Height = -11
            TitleFont.Name = 'Tahoma'
            TitleFont.Style = []
          end
        end
        object pnl2: TPanel
          Left = 1
          Top = 172
          Width = 328
          Height = 168
          Align = alClient
          BevelKind = bkFlat
          BevelOuter = bvNone
          TabOrder = 1
          object pnl4: TPanel
            Left = 0
            Top = 0
            Width = 324
            Height = 25
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Special'
            TabOrder = 0
            object dbnvgr2: TDBNavigator
              Left = 84
              Top = 0
              Width = 240
              Height = 25
              DataSource = dsSpecial
              Align = alRight
              TabOrder = 0
            end
          end
          object dbgrd4: TDBGrid
            Left = 0
            Top = 25
            Width = 324
            Height = 139
            Align = alClient
            DataSource = dsSpecial
            TabOrder = 1
            TitleFont.Charset = DEFAULT_CHARSET
            TitleFont.Color = clWindowText
            TitleFont.Height = -11
            TitleFont.Name = 'Tahoma'
            TitleFont.Style = []
          end
        end
      end
      object pnl14: TPanel
        Left = 650
        Top = 0
        Width = 327
        Height = 341
        Align = alLeft
        BevelKind = bkFlat
        BevelOuter = bvNone
        TabOrder = 2
        object pnl43: TPanel
          Left = 0
          Top = 0
          Width = 323
          Height = 25
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Restricrtions'
          TabOrder = 0
          object dbnvgr23: TDBNavigator
            Left = 83
            Top = 0
            Width = 240
            Height = 25
            DataSource = dsRestriction
            Align = alRight
            TabOrder = 0
          end
        end
        object dbgrdRestrictions: TDBGrid
          Left = 0
          Top = 25
          Width = 323
          Height = 141
          Align = alTop
          DataSource = dsRestriction
          TabOrder = 1
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
          Columns = <
            item
              Expanded = False
              FieldName = 'ID'
              ReadOnly = True
              Visible = False
            end
            item
              Expanded = False
              FieldName = 'RestDesceiption'
              Title.Caption = 'Desceiption'
              Width = 264
              Visible = True
            end>
        end
      end
      object chkLog: TCheckBox
        Left = 1000
        Top = 3
        Width = 97
        Height = 17
        Caption = 'Log file'
        Checked = True
        State = cbChecked
        TabOrder = 3
        OnClick = chkLogClick
      end
      object chkSqlLog: TCheckBox
        Left = 1103
        Top = 3
        Width = 97
        Height = 17
        Caption = 'SQL Log'
        Checked = True
        State = cbChecked
        TabOrder = 4
        OnClick = chkSqlLogClick
      end
    end
  end
  object stat1: TStatusBar
    Left = 0
    Top = 516
    Width = 1231
    Height = 19
    Panels = <>
  end
  object lv1: TListView
    Left = 0
    Top = 372
    Width = 1087
    Height = 144
    Align = alClient
    Columns = <
      item
        Caption = 'Time'
        Width = 80
      end
      item
        Caption = 'Event'
        Width = 800
      end
      item
        Caption = 'Type'
        Width = 120
      end>
    GridLines = True
    ReadOnly = True
    TabOrder = 2
    ViewStyle = vsReport
  end
  object pnl15: TPanel
    Left = 1087
    Top = 372
    Width = 144
    Height = 144
    Align = alRight
    BevelOuter = bvNone
    TabOrder = 3
    object lbl2: TLabel
      Left = 0
      Top = 0
      Width = 144
      Height = 13
      Align = alTop
      Caption = '    Preview'
      ExplicitWidth = 50
    end
    object dbimgPreview: TDBImage
      Left = 10
      Top = 19
      Width = 120
      Height = 120
      DataField = 'Preview'
      DataSource = dsUserItems
      ReadOnly = True
      TabOrder = 0
    end
  end
  object mm1: TMainMenu
    Left = 36
    Top = 142
    object U1: TMenuItem
      Caption = 'Users'
      object Adduser1: TMenuItem
        Action = actAddUser
      end
      object Edituser1: TMenuItem
        Action = actEditUser
      end
      object N19: TMenuItem
        Caption = '-'
      end
      object Weaponsonly2: TMenuItem
        Action = actWeapons
        AutoCheck = True
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Deactivateuser1: TMenuItem
        Action = actSoftDeleteUser
      end
      object ActivateUser1: TMenuItem
        Action = actRestoreUser
      end
      object N2: TMenuItem
        Caption = '-'
        Checked = True
      end
      object Deleteuser1: TMenuItem
        Action = actDeleteUser
      end
    end
    object Items1: TMenuItem
      Caption = 'Items'
      object AddItem1: TMenuItem
        Action = actAddItem
      end
      object EditItem1: TMenuItem
        Action = actEditItem
      end
      object N6: TMenuItem
        Caption = '-'
      end
      object actSellTo1: TMenuItem
        Action = actSellTo
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object DeleteItem1: TMenuItem
        Action = actDeleteItem
      end
      object N11: TMenuItem
        Caption = '-'
      end
      object StickonWeapon1: TMenuItem
        Action = actStick
      end
    end
    object ransactions1: TMenuItem
      Caption = 'Transactions'
      object Softdelete1: TMenuItem
        Action = actSoftDeleteTransaction
      end
      object actActivate1: TMenuItem
        Action = actRestoreTtransaction
      end
      object N16: TMenuItem
        Caption = '-'
      end
      object Cancel1: TMenuItem
        Action = actCanceTransaction
      end
      object N9: TMenuItem
        Caption = '-'
      end
      object Delete1: TMenuItem
        Action = actDeleteTransaction
      end
    end
    object Analitics1: TMenuItem
      Caption = 'Analytics'
      object Dashboard1: TMenuItem
        Action = actDashboard
      end
    end
  end
  object dsUsers: TDataSource
    DataSet = fdqryUsers
    Left = 348
    Top = 136
  end
  object fdqryUsers: TFDQuery
    BeforeOpen = fdqryInsertBeforeOpen
    AfterScroll = fdqryUsersAfterScroll
    OnUpdateError = fdqryUsersUpdateError
    BeforeExecute = fdqryInsertBeforeExecute
    Connection = con1
    Transaction = fdtrans1
    UpdateOptions.AssignedValues = [uvGeneratorName, uvCheckRequired]
    UpdateOptions.GeneratorName = '"Users_ID_seq"'
    UpdateOptions.CheckRequired = False
    UpdateOptions.KeyFields = 'ID'
    UpdateObject = fdpdtsqlUsers
    Left = 36
    Top = 312
  end
  object con1: TFDConnection
    Params.Strings = (
      'Password=7567'
      'User_Name=postgres'
      'Server=127.0.0.1'
      'CharacterSet=WIN1251'
      'Database=WeaponDB'
      'DriverID=PG')
    UpdateOptions.AssignedValues = [uvGeneratorName]
    UpdateOptions.GeneratorName = '"Users_ID_seq"'
    LoginPrompt = False
    Transaction = fdtrans1
    Left = 188
    Top = 136
  end
  object fdtrans1: TFDTransaction
    Connection = con1
    Left = 364
    Top = 73
  end
  object fdqryUserItems: TFDQuery
    BeforeOpen = fdqryInsertBeforeOpen
    AfterScroll = fdqryUserItemsAfterScroll
    MasterSource = dsUsers
    MasterFields = 'ID'
    BeforeExecute = fdqryInsertBeforeExecute
    Connection = con1
    Transaction = fdtrans1
    Left = 164
    Top = 312
    ParamData = <
      item
        Name = 'OwnerID'
        DataType = ftInteger
      end>
  end
  object dsUserItems: TDataSource
    DataSet = fdqryUserItems
    Left = 36
    Top = 248
  end
  object fdqryUserStikers: TFDQuery
    BeforeOpen = fdqryInsertBeforeOpen
    BeforeExecute = fdqryInsertBeforeExecute
    Connection = con1
    Transaction = fdtrans1
    Left = 832
    Top = 312
  end
  object dsStikers: TDataSource
    DataSet = fdqryUserStikers
    Left = 512
    Top = 136
  end
  object actlst1: TActionList
    Left = 280
    Top = 176
    object actAddUser: TAction
      Category = 'Users'
      Caption = 'Add user'
      Hint = 'Add new user'
      OnExecute = actAddUserExecute
    end
    object actEditUser: TAction
      Category = 'Users'
      Caption = 'Edit user'
      OnExecute = actEditUserExecute
    end
    object actDeleteUser: TAction
      Category = 'Users'
      Caption = 'Delete user'
      Hint = 'Delete current user'
      OnExecute = actDeleteUserExecute
    end
    object actSoftDeleteUser: TAction
      Category = 'Users'
      Caption = 'Soft delete'
      Hint = 'Soft delete current user'
      OnExecute = actSoftDeleteUserExecute
    end
    object actRestoreUser: TAction
      Category = 'Users'
      Caption = 'Restore'
      Hint = 'Restore current user'
      OnExecute = actRestoreUserExecute
    end
    object actAddItem: TAction
      Category = 'Items'
      Caption = 'Add Item'
      OnExecute = actAddItemExecute
    end
    object actEditItem: TAction
      Category = 'Items'
      Caption = 'Edit Item'
      OnExecute = actEditItemExecute
    end
    object actDeleteItem: TAction
      Category = 'Items'
      Caption = 'Delete Item'
      OnExecute = actDeleteItemExecute
    end
    object actSellTo: TAction
      Category = 'Items'
      Caption = 'Sell to'
      Hint = 'Sell item To...'
      OnExecute = actSellToExecute
    end
    object actDeleteTransaction: TAction
      Category = 'Transactions'
      Caption = 'Delete'
      Hint = 'Delete transaction'
      OnExecute = actDeleteTransactionExecute
    end
    object actCanceTransaction: TAction
      Category = 'Transactions'
      Caption = 'Cancel'
      OnExecute = actCanceTransactionExecute
    end
    object actStick: TAction
      Category = 'Items'
      Caption = 'Apply to a Weapon'
      Hint = 'Apply item to a weapon'
      OnExecute = actStickExecute
      OnUpdate = actStickUpdate
    end
    object actRestoreTtransaction: TAction
      Category = 'Transactions'
      Caption = 'Restore'
      OnExecute = actRestoreTtransactionExecute
    end
    object actSoftDeleteTransaction: TAction
      Category = 'Transactions'
      Caption = 'Soft delete'
      OnExecute = actSoftDeleteTransactionExecute
    end
    object actDashboard: TAction
      Category = 'Items'
      Caption = 'Dashboard'
      OnExecute = actDashboardExecute
    end
    object actPickValue: TAction
      Category = 'Items'
      Caption = 'Copy value'
      OnExecute = actPickValueExecute
    end
    object actWeapons: TAction
      Category = 'Users'
      AutoCheck = True
      Caption = 'Weapons only'
      OnExecute = rg1Click
    end
  end
  object fdpdtsqlUsers: TFDUpdateSQL
    Connection = con1
    Left = 36
    Top = 368
  end
  object pm1: TPopupMenu
    Left = 36
    Top = 184
    object Pickvalue1: TMenuItem
      Action = actPickValue
    end
    object N12: TMenuItem
      Caption = '-'
    end
    object Adduser2: TMenuItem
      Action = actAddUser
    end
    object Edituser2: TMenuItem
      Action = actEditUser
    end
    object N18: TMenuItem
      Caption = '-'
    end
    object Weaponsonly1: TMenuItem
      Action = actWeapons
      AutoCheck = True
    end
    object N3: TMenuItem
      Caption = '-'
    end
    object Deactivateuser2: TMenuItem
      Action = actSoftDeleteUser
    end
    object ActivateUser2: TMenuItem
      Action = actRestoreUser
    end
    object N4: TMenuItem
      Caption = '-'
    end
    object Deleteuser2: TMenuItem
      Action = actDeleteUser
    end
  end
  object dsItems: TDataSource
    DataSet = fdqryItems
    Left = 396
    Top = 136
  end
  object fdqryItems: TFDQuery
    BeforeOpen = fdqryInsertBeforeOpen
    BeforeExecute = fdqryInsertBeforeExecute
    Connection = con1
    UpdateOptions.AssignedValues = [uvGeneratorName]
    UpdateOptions.GeneratorName = '"Items_ID_seq"'
    UpdateOptions.KeyFields = 'ID'
    Left = 94
    Top = 316
  end
  object dsItemTypes: TDataSource
    DataSet = fdqryItemTypes
    Left = 568
    Top = 136
  end
  object dsSpecial: TDataSource
    DataSet = fdqrySpecial
    Left = 696
    Top = 136
  end
  object fdqryItemTypes: TFDQuery
    Connection = con1
    Transaction = fdtrans1
    UpdateOptions.AssignedValues = [uvGeneratorName]
    UpdateOptions.GeneratorName = '"ItemTypes_TypeID_seq"'
    UpdateOptions.KeyFields = 'TypeID'
    SQL.Strings = (
      'SELECT "TypeID", "Description" FROM "ItemTypes"')
    Left = 480
    Top = 312
  end
  object fdqryWeaponID: TFDQuery
    Connection = con1
    Transaction = fdtrans1
    UpdateOptions.AssignedValues = [uvGeneratorName]
    UpdateOptions.GeneratorName = '"StickersOnWeapon_ID_seq"'
    UpdateOptions.KeyFields = 'WeaponID'
    SQL.Strings = (
      
        'SELECT "WeaponID", "Weapon" FROM "WeaponIDToWeapon" ORDER BY "We' +
        'apon"')
    Left = 560
    Top = 312
  end
  object fdqrySpecial: TFDQuery
    Connection = con1
    Transaction = fdtrans1
    UpdateOptions.AssignedValues = [uvGeneratorName]
    UpdateOptions.GeneratorName = '"SpecialToCategory_SpecialID_seq"'
    UpdateOptions.KeyFields = 'SpecialID'
    SQL.Strings = (
      'SELECT "SpecialID", "Category" FROM "SpecialToCategory"')
    Left = 632
    Top = 312
  end
  object dsWeaponID: TDataSource
    DataSet = fdqryWeaponID
    Left = 632
    Top = 136
  end
  object dsRestriction: TDataSource
    DataSet = fdqryRestriction
    Left = 752
    Top = 136
  end
  object fdqryRestriction: TFDQuery
    Connection = con1
    Transaction = fdtrans1
    UpdateOptions.AssignedValues = [uvGeneratorName]
    UpdateOptions.GeneratorName = '"RestrictionType_ID_seq"'
    UpdateOptions.KeyFields = 'ID'
    SQL.Strings = (
      '')
    Left = 248
    Top = 312
  end
  object fdqryInsert: TFDQuery
    BeforeOpen = fdqryInsertBeforeOpen
    BeforeExecute = fdqryInsertBeforeExecute
    Connection = con1
    Transaction = fdtrans1
    Left = 324
    Top = 312
  end
  object fdqryTransaction: TFDQuery
    BeforeOpen = fdqryInsertBeforeOpen
    BeforeExecute = fdqryInsertBeforeExecute
    Connection = con1
    UpdateOptions.AssignedValues = [uvGeneratorName]
    UpdateOptions.GeneratorName = '"Transactions_TransactionID_seq"'
    UpdateOptions.KeyFields = 'TransactionID'
    Left = 396
    Top = 312
  end
  object dsTransaction: TDataSource
    DataSet = fdqryTransaction
    Left = 452
    Top = 136
  end
  object pm2: TPopupMenu
    Left = 92
    Top = 184
    object Pickvalue3: TMenuItem
      Action = actPickValue
    end
    object N14: TMenuItem
      Caption = '-'
    end
    object AddItem2: TMenuItem
      Action = actAddItem
    end
    object EditItem2: TMenuItem
      Action = actEditItem
    end
    object N7: TMenuItem
      Caption = '-'
    end
    object Sellto1: TMenuItem
      Action = actSellTo
    end
    object N8: TMenuItem
      Caption = '-'
    end
    object Deleteuser3: TMenuItem
      Action = actDeleteItem
    end
  end
  object pm3: TPopupMenu
    Left = 148
    Top = 184
    object Pickvalue4: TMenuItem
      Action = actPickValue
    end
    object N17: TMenuItem
      Caption = '-'
    end
    object Cancel2: TMenuItem
      Action = actCanceTransaction
    end
    object N15: TMenuItem
      Caption = '-'
    end
    object Softdelete2: TMenuItem
      Action = actSoftDeleteTransaction
    end
    object Restore1: TMenuItem
      Action = actRestoreTtransaction
    end
    object N10: TMenuItem
      Caption = '-'
    end
    object Delete2: TMenuItem
      Action = actDeleteTransaction
    end
  end
  object pm4: TPopupMenu
    Left = 205
    Top = 181
    object Pickvalue2: TMenuItem
      Action = actPickValue
    end
    object N13: TMenuItem
      Caption = '-'
    end
    object StickonWeapon2: TMenuItem
      Action = actStick
    end
  end
  object fdpdtsqlItems: TFDUpdateSQL
    Connection = con1
    Left = 108
    Top = 368
  end
  object fdqryPreviews: TFDQuery
    Connection = con1
    UpdateOptions.AssignedValues = [uvGeneratorName]
    Left = 696
    Top = 312
  end
  object fdqryLock: TFDQuery
    Connection = con1
    Transaction = fdtrans1
    FetchOptions.AssignedValues = [evMode, evRowsetSize, evUnidirectional, evCursorKind]
    FetchOptions.Mode = fmAll
    FetchOptions.CursorKind = ckForwardOnly
    FetchOptions.Unidirectional = True
    FetchOptions.RowsetSize = 1
    ResourceOptions.AssignedValues = [rvSilentMode]
    ResourceOptions.SilentMode = True
    UpdateOptions.AssignedValues = [uvEDelete, uvEInsert, uvEUpdate, uvLockWait]
    UpdateOptions.EnableDelete = False
    UpdateOptions.EnableInsert = False
    UpdateOptions.EnableUpdate = False
    Left = 763
    Top = 314
  end
end
