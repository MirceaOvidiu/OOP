import kotlin.random.Random

class Money {
    private var amount = Random.nextInt(0, 100)

    init {
        println("Instantiated Money object with an amount of: $amount")
    }

    fun getAmount(): Int {
        return amount
    }
}

fun over50(objects: Array<Money>) {
    for (i in 0..4) {
        val tempAmount = objects[i].getAmount()
        if (tempAmount > 50) {
            println("amount of index $i and of value $tempAmount is greater than 50")
        }
    }
}

fun main() {
    val moneyArray = Array(5) { Money() }

    over50(moneyArray)
}