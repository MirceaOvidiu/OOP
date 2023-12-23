import java.io.File

class Singleton{
    init {
        println("Logger started...")
    }

    init{
        println("error logging session started...")
    }

    fun consoleLog() {
        println("log error:")
        val message = readlnOrNull() ?: ""
        File("kt_log.txt").appendText("$message\n")
    }
}

fun main() {
    val logger = Singleton()
    logger.consoleLog()
    logger.consoleLog()
    logger.consoleLog()
}