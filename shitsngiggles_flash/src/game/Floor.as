package game {
	import net.flashpunk.graphics.Spritemap;
	/**
	 * ...
	 * @author Van Phelan
	 */
	public class Floor extends Elemental {
		
		[Embed(source = '../assets/graphics/floor.png')]
		public static const imgFloor:Class;
		[Embed(source = '../assets/graphics/floorFire.png')]
		public static const imgFloorFire:Class;
		[Embed(source = '../assets/graphics/floorWater.png')]
		public static const imgFloorWater:Class;
		[Embed(source = '../assets/graphics/floorEarth.png')]
		public static const imgFloorEarth:Class;
		[Embed(source = '../assets/graphics/floorPlant.png')]
		public static const imgFloorPlant:Class;
		
		private const sprFloor:Spritemap = new Spritemap(imgFloor, 16, 16);
		private const sprFloorFire:Spritemap = new Spritemap(imgFloorFire, 16, 16);
		private const sprFloorWater:Spritemap = new Spritemap(imgFloorWater, 16, 16);
		private const sprFloorEarth:Spritemap = new Spritemap(imgFloorEarth, 16, 16);
		private const sprFloorPlant:Spritemap = new Spritemap(imgFloorPlant, 16, 16);
		
		public function Floor(element:uint) {
			super(FLOOR, element);
			layer = 4;
			type = "floor";
			setHitbox(16, 16);
			switch (element) {
				case BLANK:
				case ABSORB: {
					graphic = sprFloor;
				}
				break;
				case FIRE: {
					graphic = sprFloorFire;
				}
				break;
				case WATER: {
					graphic = sprFloorWater;
				}
				break;
				case EARTH: {
					graphic = sprFloorEarth;
				}
				break;
				case PLANT: {
					graphic = sprFloorPlant;
				}
				break;
			}
		}
		
		override public function update():void {
			super.update();
			
			if (elementChanging) {
				switch (element) {
					case BLANK:
					case ABSORB: {
						graphic = sprFloor;
					}
					break;
					case FIRE: {
						graphic = sprFloorFire;
					}
					break;
					case WATER: {
						graphic = sprFloorWater;
					}
					break;
					case EARTH: {
						graphic = sprFloorEarth;
					}
					break;
					case PLANT: {
						graphic = sprFloorPlant;
					}
					break;
				}
			}
		}
		
	}

}