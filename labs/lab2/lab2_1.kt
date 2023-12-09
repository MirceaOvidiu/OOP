import java.time.LocalDateTime

class Time {
    val rn = LocalDateTime.now()

    init {
        println("Object created at: $rn")
    }
}

fun main() {
    val myClass = Time()
}