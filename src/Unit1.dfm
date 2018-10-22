object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Disk Not Sleep'
  ClientHeight = 321
  ClientWidth = 298
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Noto Sans CJK TC Regular'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 16
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 55
    Height = 16
    Caption = #30913#30879#20301#32622#65306
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Noto Sans CJK TC Regular'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 25
    Top = 143
    Width = 242
    Height = 48
    Caption = #36889#20491#31243#24335#33021#22816#30456#38548#19968#27573#26178#38291#20839#22312#25351#23450#30340#30913#30879#20013#23531#20837#19968#20491#38750#24120#23567#30340#27284#26696#65292#29992#20197#38450#27490#26576#20491#30913#30879#25110#26159#22806#25509#35037#32622#36914#20837#20241#30496#29376#24907#12290
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Noto Sans CJK TC Regular'
    Font.Style = []
    ParentFont = False
    WordWrap = True
  end
  object Label3: TLabel
    Left = 16
    Top = 62
    Width = 66
    Height = 16
    Caption = #32233#34909#21312#26178#38291#65306
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Noto Sans CJK TC Regular'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 16
    Top = 220
    Width = 121
    Height = 16
    Caption = #38450#24608#36895#26283#23384#27284#26696#32233#34909#21312#65306
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Noto Sans CJK TC Regular'
    Font.Style = []
    ParentFont = False
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 122
    Width = 265
    Height = 81
    Caption = #35498#26126
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Noto Sans CJK TC Regular'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
  end
  object ComboBox1: TComboBox
    Left = 16
    Top = 35
    Width = 265
    Height = 24
    AutoComplete = False
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Noto Sans CJK TC Regular'
    Font.Style = []
    ParentFont = False
    Sorted = True
    TabOrder = 0
  end
  object ProgressBar1: TProgressBar
    Left = 16
    Top = 239
    Width = 265
    Height = 17
    DoubleBuffered = True
    ParentDoubleBuffered = False
    MarqueeInterval = 1
    Step = 10000
    TabOrder = 2
  end
  object Button1: TButton
    Left = 16
    Top = 272
    Width = 153
    Height = 33
    Caption = #21855#29992
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Noto Sans CJK TC Regular'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 175
    Top = 272
    Width = 106
    Height = 33
    Caption = #32080#26463
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Noto Sans CJK TC Regular'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = Button2Click
  end
  object ComboBox2: TComboBox
    Left = 16
    Top = 81
    Width = 265
    Height = 24
    AutoComplete = False
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Noto Sans CJK TC Regular'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    Items.Strings = (
      '5 '#31186
      '10 '#31186
      '30 '#31186
      '1 '#20998#37912
      '3 '#20998#37912
      '5 '#20998#37912
      '30 '#20998#37912
      '1 '#23567#26178
      '3 '#23567#26178
      '5 '#23567#26178)
  end
  object TrayIcon1: TTrayIcon
    Hint = 'Disk Not Sleep'
    BalloonHint = #38450#24608#36895#26283#23384#27284#26696#23559#26371#22312#32972#26223#24037#20316#22519#34892#65292#27442#38364#38281#35531#36879#36942#36575#39636#20013#30340#32080#26463#25353#37397#21363#21487#12290
    BalloonTitle = 'Disk Not Sleep'
    BalloonTimeout = 3000
    OnBalloonClick = TrayIcon1BalloonClick
    OnClick = TrayIcon1Click
    Left = 152
    Top = 208
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 184
    Top = 208
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 10
    OnTimer = Timer2Timer
    Left = 216
    Top = 208
  end
  object ApplicationEvents1: TApplicationEvents
    OnMinimize = ApplicationEvents1Minimize
    Left = 248
    Top = 208
  end
end
