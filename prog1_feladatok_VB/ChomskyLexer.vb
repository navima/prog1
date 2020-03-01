Imports System
Imports System.Console
Imports System.Text.RegularExpressions

Module ChomskyLexer
	Sub Main(args As String())
		Do
			Dim be As String = ReadLine()
			Dim pattern As String = "[0-9]*(\.[0-9]+)?"
			Dim realnums As Integer = 0

			be = Regex.Replace(be, pattern, Function(match As Match)
												If match.Length > 0 Then
													realnums += 1
													Return "<real num: " + Convert.ToSingle(match.Value).ToString() + ">" + vbNewLine
												End If
												Return match.Value
											End Function)

			WriteLine(be)
			WriteLine(realnums)
		Loop
	End Sub
End Module
