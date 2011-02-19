package game {
	import net.flashpunk.graphics.Image;
	import net.flashpunk.graphics.Spritemap;
	/**
	 * ...
	 * @author Van Phelan
	 */
	public class Golem extends Elemental {
		
		//[Embed(source = '../assets/graphics/golem.png')]
		//public static const imgGolem:Class;
		//[Embed(source = '../assets/graphics/golemFire.png')]
		//public static const imgGolemFire:Class;
		//[Embed(source = '../assets/graphics/golemWater.png')]
		//public static const imgGolemWater:Class;
		//[Embed(source = '../assets/graphics/golemEarth.png')]
		//public static const imgGolemEarth:Class;
		//[Embed(source = '../assets/graphics/golemPlant.png')]
		//public static const imgGolemPlant:Class;
		//
		//private const sprGolem:Spritemap = new Spritemap(imgGolem, 16, 16);
		//private const sprGolemFire:Spritemap = new Spritemap(imgGolemFire, 16, 16);
		//private const sprGolemWater:Spritemap = new Spritemap(imgGolemWater, 16, 16);
		//private const sprGolemEarth:Spritemap = new Spritemap(imgGolemEarth, 16, 16);
		//private const sprGolemPlant:Spritemap = new Spritemap(imgGolemPlant, 16, 16);
		
		[Embed(source = '../assets/graphics/elemental.png')]
		public static const imgGolem:Class;
		
		private const sprGolem:Spritemap = new Spritemap(imgGolem, 16, 16);
		
		private var _speed:uint;
		private var _shootingInterval:uint;	// If 0, Golem does not shoot
		private var _aimAtPlayer:Boolean;	// If false, Golem shoots forward
		
		public function Golem(element:uint = ABSORB, speed:uint = 0, shootingInterval:uint = 0, aimAtPlayer:Boolean = false) {
			super(element);
			_speed = speed;
			_shootingInterval = shootingInterval;
			_aimAtPlayer = aimAtPlayer;
			layer = 2;
			type = "golem";
			setHitbox(16, 16);
			graphic = sprGolem;
			
			sprGolem.add("golemBlank",	[0]);
			sprGolem.add("golemAbsorb",	[0]);
			sprGolem.add("golemFire",	[1]);
			sprGolem.add("golemWater",	[2]);
			sprGolem.add("golemEarth",	[3]);
			sprGolem.add("golemPlant",	[4]);
			sprGolem.add("golemIce",	[5]);
			sprGolem.add("golemIron",	[6]);
			switch (element) {
				case BLANK: {
					sprGolem.play("golemBlank");
				}
				break;
				case ABSORB: {
					sprGolem.play("golemAbsorb");
				}
				break;
				case FIRE: {
					sprGolem.play("golemFire");
				}
				break;
				case WATER: {
					sprGolem.play("golemWater");
				}
				break;
				case EARTH: {
					sprGolem.play("golemEarth");
				}
				break;
				case PLANT: {
					sprGolem.play("golemPlant");
				}
				break;
				case ICE: {
					sprGolem.play("golemIce");
				}
				break;
				case IRON: {
					sprGolem.play("golemIron");
				}
				break;
			}
		}
		
		override public function update():void {
			super.update();
			
			if (elementChanging) {
				switch (element) {
					case BLANK: {
						sprGolem.play("golemBlank");
					}
					break;
					case ABSORB: {
						sprGolem.play("golemAbsorb");
					}
					break;
					case FIRE: {
						sprGolem.play("golemFire");
					}
					break;
					case WATER: {
						sprGolem.play("golemWater");
					}
					break;
					case EARTH: {
						sprGolem.play("golemEarth");
					}
					break;
					case PLANT: {
						sprGolem.play("golemPlant");
					}
					break;
					case ICE: {
						sprGolem.play("golemIce");
					}
					break;
					case IRON: {
						sprGolem.play("golemIron");
					}
					break;
				}
			}
		}
		
		public function react(otherElement:uint):void {
			if (element == BLANK || otherElement == BLANK || otherElement == ABSORB) {
				return;
			}
		}
		
	}

}