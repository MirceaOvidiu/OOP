abstract class Country {
    abstract fun printName()
    abstract fun printCapital()
    abstract fun printFavFood()

    fun printCountryDetails() {
        printName()
        printCapital()
        printFavFood()
    }
}

class Romania : Country() {
    override fun printName() {
        println("Romania")
    }

    override fun printCapital() {
        println("Bucharest")
    }

    override fun printFavFood() {
        println("Sarmale \n")
    }
}

class France : Country() {
    override fun printName() {
        println("France")
    }

    override fun printCapital() {
        println("Paris")
    }

    override fun printFavFood() {
        println("Escargot \n")
    }
}

class Germany : Country() {
    override fun printName() {
        println("Deutschland")
    }

    override fun printCapital() {
        println("Berlin")
    }

    override fun printFavFood() {
        println("Sauerkraut \n")
    }
}

fun main(){
    var ro = Romania()
    ro.printCountryDetails()

    var fr = France()
    fr.printCountryDetails()

    var de = Germany()
    de.printCountryDetails()

}



