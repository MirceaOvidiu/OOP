class Processor {
    fun freeze() {
        println("Processor freeze")
    }

    fun jump(position: Long) {
        println("Jump to position $position")
    }

    fun execute() {
        println("Processor execute")
    }
}

class Memory {
    fun load(position: Long, data: Char) {
        println("Load from position $position data: $data")
    }
}

class HardDrive {
    fun read(lba: Long, size: Int): Char {
        return 'd' // doar pt exemplu
    }
}

class Computer {
    private val processor = Processor()
    private val memory = Memory()
    private val hardDrive = HardDrive()

    fun startComputer() {
        println("Computer started... \n")
        processor.freeze()
        memory.load(1000, hardDrive.read(1000, 200))
        processor.jump(1000)
        processor.execute()
    }
}

fun main() {
    val computer = Computer()
    computer.startComputer()
}