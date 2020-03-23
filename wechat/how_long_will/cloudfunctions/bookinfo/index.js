var rq = require('request-promise')

exports.main = async(event, context) => {
  var res = rq('https://douban.uieee.com/v2/book/isbn/' + event.isbn).then(
    html => {
      return html;
    }
  ).catch(err => {
    console.log(err);
  })

  return res
}