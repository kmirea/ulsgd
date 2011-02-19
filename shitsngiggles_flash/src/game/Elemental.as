package game {
	import net.flashpunk.Entity;
	import net.flashpunk.FP;
	import net.flashpunk.graphics.Spritemap;
	/**
	 * ...
	 * @author Van Phelan
	 */
	public class Elemental extends Entity {
		
		public static const BLANK:uint	= 0;
		public static const ABSORB:uint	= 1;
		public static const FIRE:uint	= 2;
		public static const WATER:uint	= 3;
		public static const EARTH:uint	= 4;
		public static const PLANT:uint	= 5;
		public static const ICE:uint	= 6;
		public static const IRON:uint	= 7;
		
		private var _element:uint;
		private var _nextElement:uint;
		private var _prevElement:uint;
		
		public function Elemental(element:uint = BLANK) {
			_element = element;
			_nextElement = element;
			_prevElement = element;
		}
		
		override public function update():void 
		{
			_prevElement = _element;
			_element = _nextElement;
			if (elementChanging) {
				trace(this + " changing from " + this._prevElement + " to " + this._element + ".");
			}
		}
		
		public function get element():uint {
			return _element;
		}
		
		public function set element(value:uint):void {
			_nextElement = value;
		}
		
		public function get elementChanging():Boolean {
			return _element != _prevElement;
		}
		
	}

}