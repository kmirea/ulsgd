package game 
{
	import net.flashpunk.graphics.Spritemap;
	/**
	 * ...
	 * @author ...
	 */
	public class Tile extends Elemental {
		
		public static const WALL:uint	= 0;
		public static const FLOOR:uint	= 1;
		
		[Embed(source = '../assets/graphics/elemental.png')]
		public static const imgTile:Class;
		
		private const sprTile:Spritemap = new Spritemap(imgTile, 16, 16);
		
		public function Tile(type:uint = FLOOR, element:uint = BLANK) {
			super(element);
			layer = 4;
			if (type == WALL) {
				this.type = "wall";
			}
			else if (type == FLOOR) {
				this.type = "floor";
			}
			setHitbox(16, 16);
			graphic = sprTile;
			
			sprTile.add("wallBlank",	[7]);
			sprTile.add("wallAbsorb",	[7]);
			sprTile.add("wallFire",		[8]);
			sprTile.add("wallWater",	[9]);
			sprTile.add("wallEarth",	[10]);
			sprTile.add("wallPlant",	[11]);
			sprTile.add("wallIce",		[12]);
			sprTile.add("wallIron",		[13]);
			
			sprTile.add("floorBlank",	[14]);
			sprTile.add("floorAbsorb",	[14]);
			sprTile.add("floorFire",	[15]);
			sprTile.add("floorWater",	[16]);
			sprTile.add("floorEarth",	[17]);
			sprTile.add("floorPlant",	[18]);
			sprTile.add("floorIce",		[19]);
			sprTile.add("floorIron",	[20]);
			
			switch (type) {
				case "wall":
					switch (element) {
						case BLANK: {
							sprTile.play("wallBlank");
						}
						break;
						case ABSORB: {
							sprTile.play("wallAbsorb");
						}
						break;
						case FIRE: {
							sprTile.play("wallFire");
						}
						break;
						case WATER: {
							sprTile.play("wallWater");
						}
						break;
						case EARTH: {
							sprTile.play("wallEarth");
						}
						break;
						case PLANT: {
							sprTile.play("wallPlant");
						}
						break;
						case ICE: {
							sprTile.play("wallIce");
						}
						break;
						case IRON: {
							sprTile.play("wallIron");
						}
						break;
					}
				break;
				case "floor":
					switch (element) {
						case BLANK: {
							sprTile.play("floorBlank");
						}
						break;
						case ABSORB: {
							sprTile.play("floorAbsorb");
						}
						break;
						case FIRE: {
							sprTile.play("floorFire");
						}
						break;
						case WATER: {
							sprTile.play("floorWater");
						}
						break;
						case EARTH: {
							sprTile.play("floorEarth");
						}
						break;
						case PLANT: {
							sprTile.play("floorPlant");
						}
						break;
						case ICE: {
							sprTile.play("floorIce");
						}
						break;
						case IRON: {
							sprTile.play("floorIron");
						}
						break;
					}
				break;
			}
		}
		
	}

}