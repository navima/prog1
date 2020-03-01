Module MLeet

	Dim subs As New Dictionary(Of Char, List(Of String)) From
		{
			{"A", {"4", "/-\", "/_\", "@", "/\", "Д"}.ToList},
			{"B", {"8", "|3", "13", "|}", "|:", "|8", "18", "6", "|B", "|8", "lo", "|o", "j3", "ß"}.ToList},
			{"C", {"<", "{", "[", "(", "©", "¢"}.ToList},
			{"D", {"|)", "|}", "|]", "|>"}.ToList},
			{"E", {"3", "£", "₤", "€"}.ToList},
			{"F", {"|=", "ph", "|#", "|"""}.ToList},
			{"G", {"[", "-", "[+", "6", "C-"}.ToList},
			{"H", {"4", "|-|", "[-]", "{-}", "}-{", "}{", "|=|", "[=]", "{=}", "/-/", "(-)", ")-(", ":-:", "I+I"}.ToList},
			{"I", {"1", "|", "!", "9"}.ToList},
			{"J", {"_|", "_/", "_7", "_)", "_]", "_}"}.ToList},
			{"K", {"|<", "1<", "l<", "|{", "l{"}.ToList},
			{"L", {"|_", "|", "1", "]["}.ToList},
			{"M", {"44", "|\/|", "^^", "/\/\", "/X\", "[]\/][", "[]V[]", "][\\//][", "(V)", "//.", ".\\", "N\"}.ToList},
			{"N", {"|\|", "/\/", "/V", "][\\][", "И"}.ToList},
			{"O", {"0", "()", "[]", "{}", "<>", "Ø", "oh"}.ToList},
			{"P", {"|o", "|O", "|>", "|*", "|°", "|D", "/o", "[]D", "|7"}.ToList},
			{"Q", {"O_", "9", "(,)", "0", "kw"}.ToList},
			{"R", {"|2", "12", ".-", "|^", "l2", "Я", "®"}.ToList},
			{"S", {"5", "$", "§"}.ToList},
			{"T", {"7", "+", "7`", "'|' ", "`|` ", "~|~ ", "-|-", "']['"}.ToList},
			{"U", {"|_|", "\_\", "/_/", "\_/", "(_)", "[_]", "{_}"}.ToList},
			{"V", {"\/"}.ToList},
			{"W", {"\/\/", "(/\)", "\^/", "|/\|", "\X/", "\\'", "'//", "VV", "\_|_/", "\\//\\//", "Ш", "2u", "\V/"}.ToList},
			{"X", {"%", "*", "><", "}{", ")(", "Ж"}.ToList},
			{"Y", {"`/", "¥", "\|/", "Ч"}.ToList},
			{"Z", {"2", "5", "7_", ">_", "(/)"}.ToList},
			{"0", {"O", "D", " "}.ToList},
			{"1", {"I", "L"}.ToList},
			{"2", {"Z"}.ToList},
			{"3", {"E", "e"}.ToList},
			{"4", {"h", "A"}.ToList},
			{"5", {"S"}.ToList},
			{"6", {"b", "G"}.ToList},
			{"7", {"T", "j"}.ToList},
			{"8", {"B", "X"}.ToList},
			{"9", {"g", "J"}.ToList}
		}
	Dim random As New Random

	Sub ChomskyLeet()

		Console.OutputEncoding = Text.Encoding.Unicode

		''Test Unicode characters in console
		'For Each kar As Char In subs("E")
		'	WriteLine(kar)
		'Next

		Do
			Dim be = Console.ReadLine().ToUpper
			Dim ki = ""

			For Each kar As Char In be
				ki += If(subs.ContainsKey(kar), subs(kar)(random.Next(0, subs(kar).Count)), kar)
			Next

			Console.WriteLine(ki)
		Loop
	End Sub
End Module
