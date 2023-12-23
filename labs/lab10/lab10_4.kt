open class Handler {
    var next: Handler? = null

    open fun handle(request: Int) {
        next?.handle(request)
    }
}

class ConcreteHandler1 : Handler() {
    override fun handle(request: Int) {
        if (request == 1) {
            println("ConcreteHandler1 handled the request")
        } else {
            next?.handle(request)
        }
    }
}

class ConcreteHandler2 : Handler() {
    override fun handle(request: Int) {
        if (request == 2) {
            println("ConcreteHandler2 handled the request")
        } else {
            next?.handle(request)
        }
    }
}

fun main() {
    val handler1 = ConcreteHandler1()
    val handler2 = ConcreteHandler2()

    handler1.next = handler2

    println("Request value: 1")
    handler1.handle(1)
    println("Request value: 2")
    handler1.handle(2)
}