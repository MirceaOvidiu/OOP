interface Subscriber {
    fun update(value: Int)
}

class ConcreteSubscriber : Subscriber {
    override fun update(value: Int) {
        println("Subscriber was notified with the value: $value")
    }
}

class Publisher {
    private val subscribers = mutableListOf<Subscriber>()
    private var value: Int = 0

    fun attach(subscriber: Subscriber) {
        subscribers.add(subscriber)
    }

    fun setValue(value: Int) {
        this.value = value
        notifySubscribers()
    }

    private fun notifySubscribers() {
        for (subscriber in subscribers) {
            subscriber.update(value)
        }
    }
}

fun main() {
    val publisher = Publisher()
    val subscriber1 = ConcreteSubscriber()
    val subscriber2 = ConcreteSubscriber()

    publisher.attach(subscriber1)
    publisher.attach(subscriber2)

    publisher.setValue(10)
}