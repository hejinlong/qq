<?php

/**
 * @file
 * QQ Login by Oauth
 * @author hejinlong
 * @mail   jinlonghe@yahoo.cn
 * @site   www.drupaluser.org
 * @date   11-27-2011
 */
class QqOauth {
  /**
   * QQ login oauth config
  */
  function __construct() {
    $this->config = array(
      'oauth_consumer_key' => variable_get('key'),
      'oauth_consumer_secret' => variable_get('secret'),
      'oauth_callback' => variable_get('callback'),
      'oauth_request_token_url' => 'http://openapi.qzone.qq.com/oauth/qzoneoauth_request_token',
      'oauth_authorize_url' => 'http://openapi.qzone.qq.com/oauth/qzoneoauth_authorize',
      'oauth_request_access_token_url' => 'http://openapi.qzone.qq.com/oauth/qzoneoauth_access_token',
      'user_info_url' => 'http://openapi.qzone.qq.com/user/get_user_info',
    );
  }
  /**
  *  set config
  */
  function C($name) {
     return isset($this->config[$name]) ?  $this->config[$name] : FALSE;
  }
  /**
   *  build request url
   */
  function buildrequesturi($url, $params = array(), $oauth_token_secret = '') {
    $oauth_consumer_key = $this->C('oauth_consumer_key');
    $oauth_consumer_secret = $this->C('oauth_consumer_secret');
    $params = array_merge(array(
      'oauth_version' => '1.0',
      'oauth_signature_method' => 'HMAC-SHA1',
      'oauth_timestamp' => time(),
      'oauth_nonce' => rand(1000, 99999999),
      'oauth_consumer_key' => $oauth_consumer_key,
     ), $params);
     $encode_params = $params;
     ksort($encode_params);
     $oauth_signature = 'GET&' . urlencode($url) . '&' . urlencode(http_build_query($encode_params));
     $oauth_signature = base64_encode(hash_hmac('sha1', $oauth_signature, $oauth_consumer_secret . '&' . $oauth_token_secret, TRUE));
     $params['oauth_signature'] = $oauth_signature;
     return $url . '?' . http_build_query($params);
  }
  /**
   *  check callback of oauth token
   */
  function checkcallback() {
    if (isset($_GET['oauth_token'])) {
      if (isset($_GET['openid'])) {
        if (isset($_GET['oauth_signature'])) {
          if (isset($_GET['timestamp'])) {
            if (isset($_GET['oauth_vericode'])) {
              return TRUE;
            }
          }
        }
      }
    }
    return FALSE;
  }
  /**
   *  get contents by url
   */
  function getcontents($url) {
    $curl = curl_init();
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($curl, CURLOPT_URL, $url);
    return curl_exec($curl);
  }
  /**
   *  oauth request token
   */
  function oauthrequesttoken() {
    $url = $this->buildrequesturi($this->C('oauth_request_token_url'));
    $tmp_oauth_token = $this->getcontents($url);
    parse_str($tmp_oauth_token);
    if (isset($error_code)) {
      exit($error_code);
    }
    return array(
      'oauth_token' => $oauth_token,
      'oauth_token_secret' => $oauth_token_secret,
    );
  }
  /**
   *  authorize oauth token
  */
  function authorize($oauth_token) {
      $str = "HTTP/1.1 302 Found";
      header($str);
      $url = $this->C('oauth_authorize_url');
      $query_strings = http_build_query(array(
          'oauth_consumer_key' => $this->C('oauth_consumer_key'),
          'oauth_token' => $oauth_token,
          'oauth_callback' => $this->C('oauth_callback'),
      ));
      header('Location: ' . $url . '?' . $query_strings);
  }
  /**
   *  register user
   */
  function registeruser() {
    if ($this->checkcallback()) {
      $signature = base64_encode(hash_hmac('sha1', $_GET['openid'] . $_GET['timestamp'], $this->C('oauth_consumer_secret'), TRUE));
      if (!empty($_GET['oauth_signature']) && $signature == $_GET['oauth_signature']) {
        $_SESSION['oauth_token'] = $_GET['oauth_token'];
        $_SESSION['oauth_vericode'] = $_GET['oauth_vericode'];
        return;
      }
    }
    exit('UNKNOW REQUEST');
  }
  /**
   *  request access token
   */
  function requestaccesstoken() {
     $url = $this->buildrequesturi($this->C('oauth_request_access_token_url'), array(
          'oauth_token' => $_SESSION['oauth_token'],
          'oauth_vericode' => $_SESSION['oauth_vericode'],
      ), $_SESSION['oauth_token_secret']);
      return $this->getcontents($url);
  }
  /**
   *  save access token
   */
  function saveaccesstoken($access_token_str) {
    parse_str($access_token_str, $access_token_arr);
    if (isset($access_token_arr['error_code'])) {
       return FALSE;
    }
    else {
       return $access_token_arr;
    }
  }
  /**
   *  get user info
   */
  function getuserinfo() {
      $url = $this->buildrequesturi($this->C('user_info_url'), array(
          'oauth_token' => $_SESSION['oauth_token'],
          'openid' => $_SESSION['openid'],
      ), $_SESSION['oauth_token_secret']);
      return $this->getcontents($url);
  }
}
