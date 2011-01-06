package game {
	import net.flashpunk.graphics.Spritemap;
	/**
	 * ...
	 * @author Van Phelan
	 */
	public class Projectile extends Elemental {
		
		[Embed(source = '../assets/graphics/projectile.png')]
		public static const imgProjectile:Class;
		[Embed(source = '../assets/graphics/projectileFire.png')]
		public static const imgProjectileFire:Class;
		[Embed(source = '../assets/graphics/projectileWater.png')]
		public static const imgProjectileWater:Class;
		[Embed(source = '../assets/graphics/projectileEarth.png')]
		public static const imgProjectileEarth:Class;
		[Embed(source = '../assets/graphics/projectilePlant.png')]
		public static const imgProjectilePlant:Class;
		
		private const sprProjectile:Spritemap = new Spritemap(imgProjectile, 16, 16);
		private const sprProjectileFire:Spritemap = new Spritemap(imgProjectileFire, 16, 16);
		private const sprProjectileWater:Spritemap = new Spritemap(imgProjectileWater, 16, 16);
		private const sprProjectileEarth:Spritemap = new Spritemap(imgProjectileEarth, 16, 16);
		private const sprProjectilePlant:Spritemap = new Spritemap(imgProjectilePlant, 16, 16);
		
		public function Projectile(element:uint) {
			super(element);
			layer = 1;
			type = "projectile";
			setHitbox(16, 16);
			switch (element) {
				case BLANK:
				case ABSORB: {
					graphic = sprProjectile;
				}
				break;
				case FIRE: {
					graphic = sprProjectileFire;
				}
				break;
				case WATER: {
					graphic = sprProjectileWater;
				}
				break;
				case EARTH: {
					graphic = sprProjectileEarth;
				}
				break;
				case PLANT: {
					graphic = sprProjectilePlant;
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
						graphic = sprProjectile;
					}
					break;
					case FIRE: {
						graphic = sprProjectileFire;
					}
					break;
					case WATER: {
						graphic = sprProjectileWater;
					}
					break;
					case EARTH: {
						graphic = sprProjectileEarth;
					}
					break;
					case PLANT: {
						graphic = sprProjectilePlant;
					}
					break;
				}
			}
		}
		
	}

}