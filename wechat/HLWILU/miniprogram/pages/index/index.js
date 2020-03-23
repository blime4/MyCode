const app = getApp();
let openid;

Page({

  /**
   * 页面的初始数据
   */
  data: {
    isShowUserName:false,
    userInfo:null,
    openid:""
  },
  onGotUserInfo(e){
    app.getOpenid();
    if(e.detail.userInfo){
      let user = e.detail.userInfo;
      this.setData({
        isShowUserName:true,
        userInfo:e.detail.userInfo,
      })
      user.openid = app.globalData.openid;
      app._saveUserInfo(user);
    }else {
      app._showSettingToast('登陆需要允许授权');
    }
  },
  loginOut() {
    app._saveUserInfo(null)
    this.setData({
      isShowUserName: false
    })
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    openid = app.globalData.openid
    console.log("openid",openid)
    var that = this;
    that.setData({
      openid:openid
    })

    var user = app.globalData.userInfo;
    if(user){
      that.setData({
        isShowUserName:true,
        userInfo:user,
      })
    }else{
      app.userInfoReadyCallback = res =>{
        that.setData({
          userInfo:res.userInfo,
          isShowUserName:true
        })
      }
    }
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {
    
  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {
    
  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {
    
  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {
    
  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {
    
  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {
    
  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {
    
  }
})