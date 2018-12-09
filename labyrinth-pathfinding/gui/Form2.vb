Public Class Form2
    Private Sub TrackBar1_Scroll(sender As Object, e As EventArgs) Handles TrackBar1.Scroll
        Label1.Text = TrackBar1.Value
    End Sub

    Private Sub Form2_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        TrackBar1.Value = Module1.yuzhi
        Label1.Text = TrackBar1.Value
        If Module1.reverse Then
            CheckBox1.Checked = True
        End If
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Module1.yuzhi = TrackBar1.Value
        Module1.reverse = CheckBox1.Checked
    End Sub

End Class