Public Class Form3
    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Module1.interv = (100 - TrackBar1.Value) * 10
    End Sub

    Private Sub Form3_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        TrackBar1.Value = 100 - Module1.interv / 10
        Label1.Text = TrackBar1.Value
    End Sub

    Private Sub TrackBar1_Scroll(sender As Object, e As EventArgs) Handles TrackBar1.Scroll
        Label1.Text = TrackBar1.Value
    End Sub
End Class