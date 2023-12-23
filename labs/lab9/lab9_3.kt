class Salad {
    var name = ""
    var ingredients = arrayListOf<String>()

    fun listIngredients() {
        println("Ingredients: ")
        for (ingredient in ingredients) {
            println(ingredient)
        }
    }
}

open class SaladBuilder {
    open fun nameSalad () {}
    open fun addLettuce() {}
    open fun addTomato() {}
    open fun addCheese() {}
    open fun addDressing() {}
}

class CaesarSaladBuilder : SaladBuilder() {
    val salad = Salad()

    override fun nameSalad() {
        salad.name = "Caesar Salad"
    }

    override fun addLettuce() {
        salad.ingredients.add("Lettuce")
    }

    override fun addTomato() {
        salad.ingredients.add("Tomato")
    }

    override fun addCheese() {
        salad.ingredients.add("Cheese")
    }

    override fun addDressing() {
        salad.ingredients.add("Caesar Dressing")
    }
}

class Director {
    fun makeCaesarSalad(builder: CaesarSaladBuilder) {
        builder.nameSalad()
        builder.addLettuce()
        builder.addTomato()
        builder.addCheese()
        builder.addDressing()
    }
}

fun main() {
    val director = Director()
    val builder = CaesarSaladBuilder()
    director.makeCaesarSalad(builder)
    println("Salad: ${builder.salad.name}")
    builder.salad.listIngredients()
}