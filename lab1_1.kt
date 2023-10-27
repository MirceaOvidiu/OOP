public class Student
{
    val name = "Mircea"
    val surname = "Dodi"
    val group = "311AC"

    val dsa_pros = """pro: 
    laboratoare concise, 
    informatiile din lab erau 
    cele necesare pt a intelege si aprofunda,
    accent pus pe cautat
    si inteles logic,
    intrebarile si colocviul de tip interviu,
    teme interesanta"""

    val dsa_cons = "contra: sincer, nu prea am ce sa reprosez"

    val summer_activities = """activitati pe vara: 
    am intrat putin in cybersec, atat blue team si red team
    (ex. kali, nmap, metasploit, msfvenom, wireshark),
    criptari de mesaje in python 
    si am inceput sa aprofundez ceea ce stiam in C# pt a face 2 proiecte
    (mic joc in Unity si unul .NET), ghidat de un curs pe udemy"""

    val future_plans =  "sa gasesc practica dupa anul 2 momentan"
                
}

fun main(){
    val Me = Student();

    print(Me.name + " " + Me.surname + " " + Me.group + "\n " + Me.dsa_pros + "\n" + Me.dsa_cons + "\n" + Me.summer_activities +  "\n");
    

}