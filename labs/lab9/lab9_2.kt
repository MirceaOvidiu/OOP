open class Plane {
    open fun printInfo() {}
}

class Boeing747 : Plane() {
    init {
        println("Boeing747 assembled")
    }

    override fun printInfo() {
        println("Top Speed: Mach 0.9, Wingspan: 36m")
    }
}

class Cessna : Plane() {
    init {
        println("Cessna assembled")
    }

    override fun printInfo() {
        println("Top Speed: 483km/h, Wingspan: 11m")
    }
}

class F16 : Plane() {
    init {
        println("F16 assembled")
    }

    override fun printInfo() {
        println("Top Speed: Mach 2.0, Wingspan: 14m")
    }
}

fun main() {
    for (i in 1..3) {
        val plane = when (i) {
            1 -> Boeing747()
            2 -> Cessna()
            else -> F16()
        }
        plane.printInfo()
    }
}