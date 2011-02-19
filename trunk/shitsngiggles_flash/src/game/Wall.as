package game {
	import net.flashpunk.FP;
	import net.flashpunk.graphics.Spritemap;
	/**
	 * ...
	 * @author Van Phelan
	 */
	public class Wall extends Elemental {
		
		[Embed(source = '../assets/graphics/wall.png')]
		public static const imgWall:Class;
		[Embed(source = '../assets/graphics/wallFire.png')]
		public static const imgWallFire:Class;
		[Embed(source = '../assets/graphics/wallWater.png')]
		public static const imgWallWater:Class;
		[Embed(source = '../assets/graphics/wallEarth.png')]
		public static const imgWallEarth:Class;
		[Embed(source = '../assets/graphics/wallPlant.png')]
		public static const imgWallPlant:Class;
		
		private const sprWall:Spritemap = new Spritemap(imgWall, 16, 16);
		private const sprWallFire:Spritemap = new Spritemap(imgWallFire, 16, 16);
		private const sprWallWater:Spritemap = new Spritemap(imgWallWater, 16, 16);
		private const sprWallEarth:Spritemap = new Spritemap(imgWallEarth, 16, 16);
		private const sprWallPlant:Spritemap = new Spritemap(imgWallPlant, 16, 16);
		
		public function Wall(element:uint) {
			super(WALL, element);
			layer = 3;
			type = "wall";
			setHitbox(16, 16);
			switch (element) {
				case BLANK:
				case ABSORB: {
					graphic = sprWall;
				}
				break;
				case FIRE: {
					graphic = sprWallFire;
				}
				break;
				case WATER: {
					graphic = sprWallWater;
				}
				break;
				case EARTH: {
					graphic = sprWallEarth;
				}
				break;
				case PLANT: {
					graphic = sprWallPlant;
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
						graphic = sprWall;
					}
					break;
					case FIRE: {
						graphic = sprWallFire;
					}
					break;
					case WATER: {
						graphic = sprWallWater;
					}
					break;
					case EARTH: {
						graphic = sprWallEarth;
					}
					break;
					case PLANT: {
						graphic = sprWallPlant;
					}
					break;
				}
			}
		}
		
	}

}