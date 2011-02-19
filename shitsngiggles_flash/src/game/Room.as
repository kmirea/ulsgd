package game {
	import flash.utils.ByteArray;
	import net.flashpunk.Entity;
	import net.flashpunk.World;
	import net.flashpunk.utils.Input;
	/**
	 * ...
	 * @author Van Phelan
	 */
	public class Room extends World {
		
		[Embed(source = '../assets/rooms/test.oel', mimeType = "application/octet-stream")]
		public static const roomTest:Class;
		
		private var player:Golem;
		
		public function Room() {
			
		}
		
		override public function begin():void {
			loadRoom();
		}
		
		override public function update():void {
			super.update();
			
			if (Input.pressed("spawn")) {
				remove(player);
				player = new Golem(Elemental.ABSORB);
				player.x = 144;
				player.y = 64;
				add(player);
			}
			
			if (Input.check("up") && !player.collide("wall", player.x, player.y - 1)) {
				player.y -= 2;
			}
			else if (Input.check("down") && !player.collide("wall", player.x, player.y + 1)) {
				player.y += 2;
			}
			else if (Input.check("left") && !player.collide("wall", player.x - 1, player.y)) {
				player.x -= 2;
			}
			else if (Input.check("right") && !player.collide("wall", player.x + 1, player.y)) {
				player.x += 2;
			}
		}
		
		private function loadRoom():void {
			removeAll();
			
			var file:ByteArray = new roomTest;
			var xml:XML = new XML(file.readUTFBytes(file.length));
			
			var i:XML;
			var j:XML;
			var k:XML;
			
			// Golems
			for each (i in xml.objects.golem) {
				var golem:Golem = new Golem(Elemental.ABSORB);
				golem.x = i.@x;
				golem.y = i.@y;
				add(golem);
				player = golem;
			}
			for each (i in xml.golems.golemFire) {
				var golemFire:Golem = new Golem(Elemental.FIRE);
				golemFire.x = i.@x;
				golemFire.y = i.@y;
				add(golemFire);
			}
			for each (i in xml.golems.golemWater) {
				var golemWater:Golem = new Golem(Elemental.WATER);
				golemWater.x = i.@x;
				golemWater.y = i.@y;
				add(golemWater);
			}
			for each (i in xml.golems.golemEarth) {
				var golemEarth:Golem = new Golem(Elemental.EARTH);
				golemEarth.x = i.@x;
				golemEarth.y = i.@y;
				add(golemEarth);
			}
			for each (i in xml.golems.golemPlant) {
				var golemPlant:Golem = new Golem(Elemental.PLANT);
				golemPlant.x = i.@x;
				golemPlant.y = i.@y;
				add(golemPlant);
			}
			
			// Projectiles (not sure if we need these)
			for each (i in xml.golems.projectile) {
				var projectile:Projectile = new Projectile(Elemental.BLANK);
				projectile.x = i.@x;
				projectile.y = i.@y;
				add(projectile);
			}
			for each (i in xml.golems.projectileFire) {
				var projectileFire:Projectile = new Projectile(Elemental.FIRE);
				projectileFire.x = i.@x;
				projectileFire.y = i.@y;
				add(projectileFire);
			}
			for each (i in xml.golems.projectileWater) {
				var projectileWater:Projectile = new Projectile(Elemental.WATER);
				projectileWater.x = i.@x;
				projectileWater.y = i.@y;
				add(projectileWater);
			}
			for each (i in xml.golems.projectileEarth) {
				var projectileEarth:Projectile = new Projectile(Elemental.EARTH);
				projectileEarth.x = i.@x;
				projectileEarth.y = i.@y;
				add(projectileEarth);
			}
			for each (i in xml.golems.projectilePlant) {
				var projectilePlant:Projectile = new Projectile(Elemental.PLANT);
				projectilePlant.x = i.@x;
				projectilePlant.y = i.@y;
				add(projectilePlant);
			}
			
			// Floors
			for each (i in xml.tiles.floor) {
				var floor:Tile = new Tile("floor", Elemental.BLANK);
				floor.x = i.@x;
				floor.y = i.@y;
				add(floor);
			}
			for each (i in xml.tiles.floorFire) {
				var floorFire:Tile = new Tile("floor", Elemental.FIRE);
				floorFire.x = i.@x;
				floorFire.y = i.@y;
				add(floorFire);
			}
			for each (i in xml.tiles.floorWater) {
				var floorWater:Tile = new Tile("floor", Elemental.WATER);
				floorWater.x = i.@x;
				floorWater.y = i.@y;
				add(floorWater);
			}
			for each (i in xml.tiles.floorEarth) {
				var floorEarth:Tile = new Tile("floor", Elemental.EARTH);
				floorEarth.x = i.@x;
				floorEarth.y = i.@y;
				add(floorEarth);
			}
			for each (i in xml.tiles.floorPlant) {
				var floorPlant:Tile = new Tile("floor", Elemental.PLANT);
				floorPlant.x = i.@x;
				floorPlant.y = i.@y;
				add(floorPlant);
			}
			for each (i in xml.tiles.floorIce) {
				var floorIce:Tile = new Tile("floor", Elemental.ICE);
				floorIce.x = i.@x;
				floorIce.y = i.@y;
				add(floorIce);
			}
			for each (i in xml.tiles.floorIron) {
				var floorIron:Tile = new Tile("floor", Elemental.IRON);
				floorIron.x = i.@x;
				floorIron.y = i.@y;
				add(floorIron);
			}
			
			// Walls
			for each (i in xml.tiles.wall) {
				var wall:Tile = new Tile("wall", Elemental.BLANK);
				wall.x = i.@x;
				wall.y = i.@y;
				add(wall);
			}
			for each (i in xml.tiles.wallFire) {
				var wallFire:Tile = new Tile("wall", Elemental.FIRE);
				wallFire.x = i.@x;
				wallFire.y = i.@y;
				add(wallFire);
			}
			for each (i in xml.tiles.wallWater) {
				var wallWater:Tile = new Tile("wall", Elemental.WATER);
				wallWater.x = i.@x;
				wallWater.y = i.@y;
				add(wallWater);
			}
			for each (i in xml.tiles.wallEarth) {
				var wallEarth:Tile = new Tile("wall", Elemental.EARTH);
				wallEarth.x = i.@x;
				wallEarth.y = i.@y;
				add(wallEarth);
			}
			for each (i in xml.tiles.wallPlant) {
				var wallPlant:Tile = new Tile("wall", Elemental.PLANT);
				wallPlant.x = i.@x;
				wallPlant.y = i.@y;
				add(wallPlant);
			}
			for each (i in xml.tiles.wallIce) {
				var wallIce:Tile = new Tile("wall", Elemental.ICE);
				wallIce.x = i.@x;
				wallIce.y = i.@y;
				add(wallIce);
			}
			for each (i in xml.tiles.wallIron) {
				var wallIron:Tile = new Tile("wall", Elemental.IRON);
				wallIron.x = i.@x;
				wallIron.y = i.@y;
				add(wallIron);
			}
		}
		
	}

}