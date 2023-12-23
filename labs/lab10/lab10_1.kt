import java.util.ArrayList

open class Component {
    open fun operation() {
        println("Component operation executed.")
    }
}

class Leaf : Component() {
    override fun operation() {
        println("Leaf operation executed.")
    }
}

class Composite : Component() {
    private val children = ArrayList<Component>()

    fun add(component: Component) {
        children.add(component)
    }

    override fun operation() {
        println("Composite operation executed.\nChildren:")
        for (c in children) {
            c.operation()
        }
    }
}

fun main(){
    val composite = Composite()
    composite.add(Leaf())
    composite.add(Leaf())
    composite.add(Leaf())
    composite.operation()
}