import kotlin.math.PI

///open class necessary
open class Beer(
    protected var type: String = "default",
    protected var origin: String = "default"
) {
    fun getBeerType(): String {
        return type
    }

    fun getBeerOrigin(): String {
        return origin
    }

    open fun printBeerDetails()
    {
        println(getBeerType() + " din " + getBeerOrigin())
    }
}

class BeerSquareLabel(type:String, origin:String, private var labelLength: Int) : Beer(type,origin)
{
    private fun getLabelArea() : Int
    {
        return labelLength*labelLength
    }

    override fun printBeerDetails() {
        println(getBeerType() + " din " + getBeerOrigin() + " cu aria etichetei:" + getLabelArea())
    }
}

class BeerRoundLabel(type:String,origin:String, private var labelRadius:Int) : Beer(type,origin)
{
    private fun getLabelArea(): Double
    {
        return (PI*labelRadius*labelRadius)
    }

    override fun printBeerDetails() {
        println(getBeerType() + " din " + getBeerOrigin() + " cu aria etichetei:" + "%.2f".format(getLabelArea()))
    }
}

class BeerRTriangleLabel(type: String,origin: String, private var labelBase:Int, private var labelHeight: Int) : Beer(type,origin)
{
    private fun getLabelArea(): Double
    {
        return labelBase*labelHeight*0.5
    }

    override fun printBeerDetails() {
        println(getBeerType() + " din " + getBeerOrigin() + " cu aria etichetei:" + getLabelArea())
    }
}

fun main()
{
    val beer1 = Beer("Ciucas","Carpati")
    beer1.printBeerDetails()

    val beer2 = BeerRoundLabel("Zaganu","Bucuresti",8)
    beer2.printBeerDetails()

    val beer3 = BeerSquareLabel("Silva","Transilvania",5)
    beer3.printBeerDetails()

    val beer4 = BeerRTriangleLabel("Timisoreana","Timisoara",5,6)
    beer4.printBeerDetails()


 }