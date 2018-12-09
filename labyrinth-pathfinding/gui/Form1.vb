Imports System.ComponentModel

Public Class Form1
    Public Declare Function LoadLibrary Lib "kernel32" Alias "LoadLibraryA" (ByVal hLibModule As String) As Integer
    Public Declare Function GetProcAddress1 Lib "kernel32" Alias "GetProcAddress" (ByVal hModule As Integer, ByVal lpProcName As String) As _clear
    Public Declare Function GetProcAddress2 Lib "kernel32" Alias "GetProcAddress" (ByVal hModule As Integer, ByVal lpProcName As String) As _initmap
    Public Declare Function GetProcAddress3 Lib "kernel32" Alias "GetProcAddress" (ByVal hModule As Integer, ByVal lpProcName As String) As _getpath

    'Public Declare Sub Sleep Lib "kernel32" (ByVal ms As Integer)

    Public Delegate Sub _clear()
    Public Delegate Sub _initmap(ByRef source As Integer, ByVal width As Integer,
                                                         ByVal height As Integer,
                                                         ByVal sx As Integer,
                                                         ByVal sy As Integer,
                                                         ByVal ex As Integer,
                                                         ByVal ey As Integer,
                                                         ByVal addr As procsub,
                                                         ByVal addr2 As finishsub,
                                                         ByVal interv As Integer)
    Public Delegate Function _getpath(ByRef result As coord) As Integer

    Public clear As _clear
    Public initmap As _initmap
    Public getpath As _getpath

    '              "C:\刘权兴\代码\sydll\Release\sydll.dll"
    'Public Declare Sub clear Lib "sydll.dll" Alias "_clear@0" ()
    'Public Declare Sub initmap Lib "sydll.dll" Alias "_initmap@40" (ByRef source As Integer,
    '                                                                                            ByVal width As Integer,
    '                                                                                            ByVal height As Integer,
    '                                                                                            ByVal sx As Integer,
    '                                                                                            ByVal sy As Integer,
    '                                                                                            ByVal ex As Integer,
    '                                                                                            ByVal ey As Integer,
    '                                                                                            ByVal addr As procsub,
    '                                                                                            ByVal addr2 As finishsub,
    '                                                                                            ByVal interv As Integer)
    'Public Declare Function getpath Lib "sydll.dll" Alias "_getpath@4" (ByRef result As coord) As Integer




    Public Delegate Sub procsub(x As Integer, y As Integer)
    Public Delegate Sub finishsub(found As Boolean)
    Public Delegate Sub startsub()
    Public Delegate Sub startinvsub()

    Public Structure coord
        Dim x As Integer
        Dim y As Integer
    End Structure

    Public procaddr As procsub = AddressOf proc
    Public finishaddr As finishsub = AddressOf finish
    Public startaddr As startsub = AddressOf start
    Public startinvaddr As startinvsub = AddressOf startinv
    Public dotsize As Integer = 0
    Public mapsizex As Integer = 60
    Public mapsizey As Integer = 40
    Public br0 = New SolidBrush(Color.White)
    Public br1 = New SolidBrush(Color.Black)
    Public br2 = New SolidBrush(Color.FromArgb(255, 54, 250, 0))
    Public br3 = New SolidBrush(Color.Green)
    Public br4 = New SolidBrush(Color.FromArgb(255, 221, 221, 221))
    Public br5 = New SolidBrush(Color.Red)
    Public scr(mapsizex * mapsizey) As Integer
    Public dot(mapsizex * mapsizey) As dottype
    Public dot_old(mapsizex * mapsizey) As dottype
    Public headx, heady As Integer
    Public publicg As Graphics
    Public filename As String
    Public sx As Integer = 0
    Public sy As Integer = 0
    Public ex As Integer = 0
    Public ey As Integer = 0
    Public settingstartpoint As Integer = 0
    Public olddotpos As Point
    Public olddot As dottype
    Public thr As Threading.Thread
    Public pathresult() As coord
    Public bodyx As Integer
    Public bodyy As Integer
    Public paramx As Integer
    Public paramy As Integer



    Public Enum dottype
        DT_BACKGROUND
        DT_WALL
        DT_HEAD
        DT_BODY
        DT_UNKNOWN
        DT_STARTPOINT
    End Enum
    Public Sub start()
        'Sleep(3000)
        initmap(scr(0), mapsizex, mapsizey, sx, sy, ex, ey, procaddr, finishaddr, interv)

    End Sub

    Public Sub startinv()
        Dim ii As Integer

        If dot(getindex(bodyx, bodyy)) = dottype.DT_HEAD Then
            dot(getindex(bodyx, bodyy)) = dottype.DT_BODY
            drawdot(publicg, bodyx, bodyy)
        End If

        bodyx = paramx
        bodyy = paramy

        If dot(getindex(paramx, paramy)) = dottype.DT_BACKGROUND Then
            dot(getindex(paramx, paramy)) = dottype.DT_HEAD
            drawdot(publicg, paramx, paramy)

            If paramx > 0 Then
                ii = getindex(paramx - 1, paramy)
                If dot(ii) = dottype.DT_UNKNOWN Then
                    dot(ii) = dottype.DT_WALL
                    drawdot(publicg, paramx - 1, paramy)
                End If
            End If
            If paramx < mapsizex - 1 Then
                ii = getindex(paramx + 1, paramy)
                If dot(ii) = dottype.DT_UNKNOWN Then
                    dot(ii) = dottype.DT_WALL
                    drawdot(publicg, paramx + 1, paramy)
                End If
            End If
            If paramy > 0 Then
                ii = getindex(paramx, paramy - 1)
                If dot(ii) = dottype.DT_UNKNOWN Then
                    dot(ii) = dottype.DT_WALL
                    drawdot(publicg, paramx, paramy - 1)
                End If
            End If
            If paramy < mapsizey - 1 Then
                ii = getindex(paramx, paramy + 1)
                If dot(ii) = dottype.DT_UNKNOWN Then
                    dot(ii) = dottype.DT_WALL
                    drawdot(publicg, paramx, paramy + 1)
                End If
            End If
        End If

    End Sub


    Sub proc(x As Integer, y As Integer)
        'Dim publicg As Graphics = PictureBox1.CreateGraphics
        paramx = x
        paramy = y
        PictureBox1.Invoke(startinvaddr)



    End Sub
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Dim i As Integer
        'Dim b As Boolean = True
        setminsize()
        'drawall()
        Label1.Parent = PictureBox1
        Label1.BackColor = Color.FromArgb(100, 255, 255, 102)
        Dim hdll As Integer = LoadLibrary("sydll.dll")
        clear = GetProcAddress1(hdll, "_clear@0")
        initmap = GetProcAddress2(hdll, "_initmap@40")
        getpath = GetProcAddress3(hdll, "_getpath@4")

        For i = 0 To mapsizex * mapsizey - 1
            'If b Then
            '    scr(i) = 0
            '    dot(i) = dottype.DT_BACKGROUND
            '    dot_old(i) = dottype.DT_BACKGROUND
            '    b = False
            'Else
            '    scr(i) = 1
            '    dot(i) = dottype.DT_WALL
            '    dot_old(i) = dottype.DT_WALL
            '    b = True
            'End If
            dot(i) = dottype.DT_BACKGROUND
        Next

    End Sub



    Public Sub finish(found As Boolean)
        Dim i As Integer
        Dim j As Integer
        Dim g As Graphics = PictureBox1.CreateGraphics
        If Not found Then
            GoTo e
        End If
        ReDim pathresult(mapsizex * mapsizey)
        i = getpath(pathresult(0))
        For j = 1 To i - 2
            dot(getindex(pathresult(j).x, pathresult(j).y)) = dottype.DT_HEAD
            drawdot(g, pathresult(j).x, pathresult(j).y)
        Next
e:
        enablebutton()
    End Sub

    Public Function getindex(x As Integer, y As Integer) As Integer
        getindex = y * mapsizex + x
    End Function

    Public Function getxy(p As Point) As Point
        Dim tmpx, tmpy As Integer
        tmpx = Int(p.X / dotsize)
        tmpy = Int(p.Y / dotsize)
        If tmpx < mapsizex Then
            getxy.X = tmpx
        Else
            getxy.X = mapsizex - 1
        End If
        If tmpy < mapsizey Then
            getxy.Y = tmpy
        Else
            getxy.Y = mapsizey - 1
        End If
    End Function

    Public Sub drawdot(ByRef g As Graphics, x As Integer, y As Integer)
        Dim tmp As dottype
        Dim tmpsize As New Rectangle(x * dotsize, y * dotsize, dotsize, dotsize)
        tmp = dot(getindex(x, y))
        Select Case tmp
            Case dottype.DT_BACKGROUND
                g.FillRectangle(br0, tmpsize)
            Case dottype.DT_WALL
                g.FillRectangle(br1, tmpsize)
            Case dottype.DT_HEAD
                g.FillRectangle(br2, tmpsize)
            Case dottype.DT_BODY
                g.FillRectangle(br3, tmpsize)
            Case dottype.DT_UNKNOWN
                g.FillRectangle(br4, tmpsize)
            Case dottype.DT_STARTPOINT
                g.FillRectangle(br0, tmpsize)
                g.FillEllipse(br5, tmpsize)
        End Select

    End Sub

    Public Sub drawall()
        Dim tmpsizex, tmpsizey, tmpsize As Integer
        tmpsizex = PictureBox1.Width / mapsizex
        tmpsizey = PictureBox1.Height / mapsizey
        If tmpsizex < tmpsizey Then
            tmpsize = tmpsizex
        Else
            tmpsize = tmpsizey
        End If
        'If dotsize = tmpsize Then
        '    Exit Sub
        'End If
        dotsize = tmpsize
        Dim x, y As Integer
        Dim g As Graphics = PictureBox1.CreateGraphics
        PictureBox1.Refresh()
        'g.Clear(Color.Transparent)
        For x = 0 To mapsizex - 1
            For y = 0 To mapsizey - 1
                drawdot(g, x, y)
            Next
        Next
    End Sub

    Public Sub setminsize()
        Me.MinimumSize = New Drawing.Size(16 + mapsizex, 147 + mapsizey)

    End Sub



    Private Sub ToolStripMenuItem3_Click(sender As Object, e As EventArgs) Handles ToolStripMenuItem3.Click
        Dim r As DialogResult
        r = OpenFileDialog1.ShowDialog()
        If r = DialogResult.Cancel Then
            Exit Sub
        End If
        filename = OpenFileDialog1.FileName
        sx = 0
        sy = 0
        ex = 0
        ey = 0
        If Not procfile(0.5, False) Then
            Exit Sub
        End If
        setminsize()
        drawall()

    End Sub

    Public Function procfile(yuzhi As Single, reverse As Boolean) As Boolean
        Dim bmp As Bitmap
        Dim x, y As Integer
        Dim b As Single
        Dim r As MsgBoxResult

        If FileIO.FileSystem.FileExists(filename) Then
            bmp = Bitmap.FromFile(filename)
            mapsizex = bmp.Width
            mapsizey = bmp.Height
            If mapsizex > 2000 Or mapsizey > 1000 Or mapsizex * mapsizey > 40000 Then
                r = MsgBox("图像尺寸过大。建议选择200x200以下的图像。是否继续？", MsgBoxStyle.YesNo, "提示")
                If r = MsgBoxResult.No Then
                    procfile = False
                    Exit Function
                End If
            End If
            ReDim dot(mapsizex * mapsizey)
            ReDim scr(mapsizex * mapsizey)
            For x = 0 To mapsizex - 1
                For y = 0 To mapsizey - 1
                    b = bmp.GetPixel(x, y).GetBrightness
                    If b < yuzhi Then
                        If reverse Then
                            dot(getindex(x, y)) = dottype.DT_BACKGROUND
                        Else
                            dot(getindex(x, y)) = dottype.DT_WALL
                        End If
                    Else
                        If reverse Then
                            dot(getindex(x, y)) = dottype.DT_WALL
                        Else
                            dot(getindex(x, y)) = dottype.DT_BACKGROUND
                        End If
                    End If
                Next
            Next
        End If
        procfile = True
    End Function

    Private Sub 调整图像ToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles 调整图像ToolStripMenuItem.Click
        Dim f2 As New Form2
        Dim r As DialogResult
        r = f2.ShowDialog()
        If r = DialogResult.Cancel Then
            Exit Sub
        End If
        procfile(Module1.yuzhi / 100, Module1.reverse)
        setminsize()
        drawall()
    End Sub

    Private Sub SetStartendPointToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SetStartendPointToolStripMenuItem.Click
        settingstartpoint = 1
        PictureBox1.Cursor = Cursors.Cross
        Label1.Text = "设置起点，按右键取消"
        Label1.Visible = True
        olddotpos.X = 0
        olddotpos.Y = 0
        olddot = dot(0)
        Dim g As Graphics = PictureBox1.CreateGraphics
        If dot(getindex(sx, sy)) = dottype.DT_STARTPOINT Then
            dot(getindex(sx, sy)) = dottype.DT_BACKGROUND
            drawdot(g, sx, sy)
        End If
        If dot(getindex(ex, ey)) = dottype.DT_STARTPOINT Then
            dot(getindex(ex, ey)) = dottype.DT_BACKGROUND
            drawdot(g, ex, ey)
        End If
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        If sx = 0 And sy = 0 And ex = 0 And ey = 0 Then
            MsgBox("请设置起点和终点", MsgBoxStyle.Information, "提示")
            Exit Sub
        End If
        disablebutton()
        Dim x, y, i As Integer
        Dim tmp As dottype
        clear()
        i = 0
        For y = 0 To mapsizey - 1
            For x = 0 To mapsizex - 1
                tmp = dot(i)
                Select Case tmp
                    Case dottype.DT_WALL
                        scr(i) = 1
                        dot(i) = dottype.DT_UNKNOWN
                    Case dottype.DT_STARTPOINT
                        scr(i) = 0
                    Case dottype.DT_UNKNOWN
                        scr(i) = 1
                    Case Else
                        scr(i) = 0
                        dot(i) = dottype.DT_BACKGROUND
                End Select
                i = i + 1
            Next
        Next
        drawall()
        publicg = PictureBox1.CreateGraphics
        thr = New Threading.Thread(AddressOf start)

        thr.Start()

    End Sub


    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Application.Exit()
    End Sub

    Private Sub Form1_SizeChanged(sender As Object, e As EventArgs) Handles Me.SizeChanged
        Dim tmpsizex, tmpsizey, tmpsize As Integer
        tmpsizex = PictureBox1.Width / mapsizex
        tmpsizey = PictureBox1.Height / mapsizey
        If tmpsizex < tmpsizey Then
            tmpsize = tmpsizex
        Else
            tmpsize = tmpsizey
        End If
        If dotsize = tmpsize Then
            Exit Sub
        End If
        dotsize = tmpsize
        drawall()
    End Sub

    Private Sub PictureBox1_Paint(sender As Object, e As PaintEventArgs) Handles PictureBox1.Paint
        'MsgBox("p")
        'Dim tmpsizex, tmpsizey, tmpsize As Integer
        'tmpsizex = PictureBox1.Width / mapsizex
        'tmpsizey = PictureBox1.Height / mapsizey
        'If tmpsizex < tmpsizey Then
        '    tmpsize = tmpsizex
        'Else
        '    tmpsize = tmpsizey
        'End If
        'If dotsize = tmpsize Then
        '    Exit Sub
        'End If

        Dim x, y As Integer
        For x = 0 To mapsizex - 1
            For y = 0 To mapsizey - 1
                drawdot(e.Graphics, x, y)
            Next
        Next

    End Sub

    Private Sub PictureBox1_MouseMove(sender As Object, e As MouseEventArgs) Handles PictureBox1.MouseMove
        Dim r As Point
        Dim g As Graphics = PictureBox1.CreateGraphics
        Dim tmpi As Integer
        If settingstartpoint Then

            r = getxy(e.Location)
            If r = olddotpos Then
                Exit Sub
            End If

            Label1.Visible = False
            Label1.Top = e.Y + 20
            Label1.Left = e.X
            Label1.Visible = True

            tmpi = getindex(r.X, r.Y)

            dot(getindex(olddotpos.X, olddotpos.Y)) = olddot
            drawdot(g, olddotpos.X, olddotpos.Y)

            olddotpos = r
            olddot = dot(tmpi)


            dot(tmpi) = dottype.DT_STARTPOINT
            drawdot(g, r.X, r.Y)
        End If

    End Sub

    Private Sub 设置速度ToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles 设置速度ToolStripMenuItem.Click
        Dim f As New Form3
        f.ShowDialog()
    End Sub

    Private Sub 退出ToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles 退出ToolStripMenuItem.Click
        Application.Exit()
    End Sub

    Private Sub PictureBox1_MouseClick(sender As Object, e As MouseEventArgs) Handles PictureBox1.MouseClick
        Dim r As Point
        Dim g As Graphics
        If settingstartpoint = 0 Then
            Exit Sub
        End If
        g = PictureBox1.CreateGraphics
        r = getxy(e.Location)
        Select Case e.Button
            Case MouseButtons.Left
                If settingstartpoint = 1 Then
                    If olddot = dottype.DT_BACKGROUND Or olddot = dottype.DT_BODY Or olddot = dottype.DT_HEAD Then
                        dot(getindex(r.X, r.Y)) = dottype.DT_STARTPOINT
                        olddot = dottype.DT_STARTPOINT
                        drawdot(g, r.X, r.Y)
                        sx = r.X
                        sy = r.Y
                        settingstartpoint = 2
                        Label1.Text = "设置终点，按右键取消"
                    End If
                ElseIf settingstartpoint = 2 Then
                    If olddot = dottype.DT_BACKGROUND Or olddot = dottype.DT_BODY Or olddot = dottype.DT_HEAD Then
                        dot(getindex(r.X, r.Y)) = dottype.DT_STARTPOINT
                        drawdot(g, r.X, r.Y)
                        ex = r.X
                        ey = r.Y
                        settingstartpoint = 0
                        PictureBox1.Cursor = Cursors.Default
                        Label1.Visible = False
                    End If
                End If
            Case MouseButtons.Right
                dot(getindex(olddotpos.X, olddotpos.Y)) = olddot
                drawdot(g, olddotpos.X, olddotpos.Y)
                If dot(getindex(sx, sy)) = dottype.DT_STARTPOINT Then
                    dot(getindex(sx, sy)) = dottype.DT_BACKGROUND
                    drawdot(g, sx, sy)
                End If
                settingstartpoint = 0
                PictureBox1.Cursor = Cursors.Default
                Label1.Visible = False
        End Select
    End Sub

    Public Sub enablebutton()
        Button1.Enabled = True
        ToolStripMenuItem3.Enabled = True
        设置速度ToolStripMenuItem.Enabled = True
        图像ToolStripMenuItem.Enabled = True
    End Sub

    Public Sub disablebutton()
        Button1.Enabled = False
        ToolStripMenuItem3.Enabled = False
        设置速度ToolStripMenuItem.Enabled = False
        图像ToolStripMenuItem.Enabled = False
    End Sub
End Class
