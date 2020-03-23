import { VantComponent } from '../common/component';
import { Weapp } from 'definitions/weapp';
import { addUnit, isDef } from '../common/utils';

const LONG_PRESS_START_TIME = 600;
const LONG_PRESS_INTERVAL = 200;

// add num and avoid float number
function add(num1: number, num2: number): number {
  const cardinal = 10 ** 10;
  return Math.round((num1 + num2) * cardinal) / cardinal;
}

VantComponent({
  field: true,

  classes: ['input-class', 'plus-class', 'minus-class'],

  props: {
    value: {
      type: null,
      observer(value) {
        if (value === '') {
          return;
        }

        const newValue = this.range(value);

        if (typeof newValue === 'number' && +this.data.value !== newValue) {
          this.setData({ value: newValue });
        }
      },
    },
    integer: Boolean,
    disabled: Boolean,
    inputWidth: {
      type: null,
      observer() {
        this.setData({
          inputStyle: this.computeInputStyle()
        });
      },
    },
    buttonSize: {
      type: null,
      observer() {
        this.setData({
          inputStyle: this.computeInputStyle(),
          buttonStyle: this.computeButtonStyle()
        });
      }
    },
    asyncChange: Boolean,
    disableInput: Boolean,
    decimalLength: {
      type: Number,
      value: null
    },
    min: {
      type: null,
      value: 1
    },
    max: {
      type: null,
      value: Number.MAX_SAFE_INTEGER
    },
    step: {
      type: null,
      value: 1
    },
    showPlus: {
      type: Boolean,
      value: true
    },
    showMinus: {
      type: Boolean,
      value: true
    },
    disablePlus: Boolean,
    disableMinus: Boolean,
    longPress: {
      type: Boolean,
      value: true
    },
  },

  data: {
    focus: false,
    inputStyle: '',
    buttonStyle: ''
  },

  created() {
    this.setData({
      value: this.range(this.data.value)
    });
  },

  methods: {
    isDisabled(type: string) {
      if (type === 'plus') {
        return this.data.disabled || this.data.disablePlus || this.data.value >= this.data.max;
      }

      return this.data.disabled || this.data.disableMinus || this.data.value <= this.data.min;
    },

    onFocus(event: Weapp.Event) {
      this.$emit('focus', event.detail);
    },

    onBlur(event: Weapp.Event) {
      const value = this.range(this.data.value);
      this.triggerInput(value);
      this.$emit('blur', event.detail);
    },

    // limit value range
    range(value) {
      value = String(value).replace(/[^0-9.-]/g, '');

      // format range
      value = value === '' ? 0 : +value;
      value = Math.max(Math.min(this.data.max, value), this.data.min);

      // format decimal
      if (isDef(this.data.decimalLength)) {
        value = value.toFixed(this.data.decimalLength);
      }

      return value;
    },

    onInput(event: Weapp.Event) {
      const { value = '' } = event.detail || {};
      this.triggerInput(value);
    },

    onChange() {
      const { type } = this;
      if (this.isDisabled(type)) {
        this.$emit('overlimit', type);
        return;
      }

      const diff = type === 'minus' ? -this.data.step : +this.data.step;
      const value = add(+this.data.value, diff);

      this.triggerInput(this.range(value));
      this.$emit(type);
    },

    longPressStep() {
      this.longPressTimer = setTimeout(() => {
        this.onChange();
        this.longPressStep();
      }, LONG_PRESS_INTERVAL);
    },

    onTap(event: Weapp.Event) {
      const { type } = event.currentTarget.dataset;
      this.type = type;
      this.onChange();
    },

    onTouchStart(event: Weapp.Event) {
      if (!this.data.longPress) {
        return;
      }
      clearTimeout(this.longPressTimer);

      const { type } = event.currentTarget.dataset;
      this.type = type;
      this.isLongPress = false;

      this.longPressTimer = setTimeout(() => {
        this.isLongPress = true;
        this.onChange();
        this.longPressStep();
      }, LONG_PRESS_START_TIME);
    },

    onTouchEnd() {
      if (!this.data.longPress) {
        return;
      }
      clearTimeout(this.longPressTimer);
    },

    triggerInput(value: string) {
      this.setData({
        value: this.data.asyncChange ? this.data.value : value
      });
      this.$emit('change', value);
    },

    computeInputStyle() {
      let style = '';

      if (this.data.inputWidth) {
        style = `width: ${addUnit(this.data.inputWidth)};`;
      }

      if (this.data.buttonSize) {
        style += `height: ${addUnit(this.data.buttonSize)};`;
      }

      return style;
    },

    computeButtonStyle() {
      let style = '';
      const size = addUnit(this.data.buttonSize);

      if (this.data.buttonSize) {
        style = `width: ${size};height: ${size};`;
      }

      return style;
    }
  }
});