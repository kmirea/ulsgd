package {
	import game.Room;
	import net.flashpunk.Engine;
	import net.flashpunk.FP;
	import net.flashpunk.utils.Input;
	import net.flashpunk.utils.Key;
	
	/**
	 * ...
	 * @author Van Phelan
	 */
	public class Main extends Engine {
		
		public function Main() {
			super(320, 240, 30, true);
			FP.screen.scale = 2;
			
			Input.define("up", Key.W, Key.UP);
			Input.define("down", Key.S, Key.DOWN);
			Input.define("left", Key.A, Key.LEFT);
			Input.define("right", Key.D, Key.RIGHT);
			Input.define("spawn", Key.SPACE);
			
			FP.world = new Room;
		}
		
	}
	
}