private class Car(val carMaker:String, val carModel:String, val carYear:String, val hp:Int)
{

    constructor(carMaker:String, carModel:String, carYear:String):this(carMaker, carModel, carYear, 0)
    {
        println("Created car: $carMaker $carModel $carYear $hp using secondary constructor")
    }

       init{
    println("Created car: $carMaker $carModel $carYear $hp by using primary constructor")
    }
}

fun main()
{
    ///primary constructor
    val car1 = Car("VW", "Touran", "2004",999)
    val car2 = Car("BMW", "e36", "1995",1)

    //secondary constructor
    val car3 = Car("Skoda", "Octavia", "2004")
    val car4 = Car("Audi", "A4", "2004")

    //la output, ultimele 2 instantieri de clasa vor afisa atat mesajul din
    //constructorul principal cat si din din cel secundar

}