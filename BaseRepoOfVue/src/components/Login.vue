<template>
  <div class="login">
    <el-card>
      <h2>Login</h2>
      <!-- <el-form     
      class="login-form"
      :model="model"
      :rules="rules"
      ref="form" 
      action="/employee-jsons/doLogin.action"
      method="post"
      >
        <el-form-item prop="username">
          <el-input v-model="model.username" name="username" placeholder="Username" prefix-icon="fas fa-user"></el-input>
        </el-form-item>
        <el-form-item prop="password">
          <el-input
            v-model="model.password"
            name="password"
            placeholder="Password"
            type="password"
            prefix-icon="fas fa-lock"
          ></el-input>
        </el-form-item>
        <el-form-item>
          <el-button
            :loading="loading"
            class="login-button"
            type="primary"
            native-type="submit"
            block
          >Login</el-button>
        </el-form-item>
        <a class="forgot-password" href="https://oxfordinformatics.com/">Forgot password ?</a>
      </el-form> -->

      <el-form class="login-form" :model="model" :rules="rules" ref="form" @submit.native.prevent="login">
        <el-form-item prop="username">
          <el-input v-model="model.username" placeholder="Username" prefix-icon="fas fa-user"></el-input>
        </el-form-item>
        <el-form-item prop="password">
          <el-input v-model="model.password" placeholder="Password" type="password" prefix-icon="fas fa-lock">
          </el-input>
        </el-form-item>
        <el-form-item>
          <el-button :loading="loading" class="login-button" type="primary" native-type="submit" block>Login</el-button>
        </el-form-item>
        <a class="forgot-password" href="https://oxfordinformatics.com/">Forgot password ?</a>
      </el-form>
    </el-card>
  </div>
</template>

<script>
  import axios from 'axios';
  import qs from 'qs';
  //Vue.prototype.$axios = axios

  export default {
    name: "login",
    data() {
      return {
        validCredentials: {
          username: "lightscope",
          password: "lightscope"
        },
        model: {
          username: "",
          password: ""
        },
        loading: false,
        success: false,
        rules: {
          username: [
            {
              required: true,
              message: "Username is required",
              trigger: "blur"
            },
            {
              min: 4,
              message: "Username length should be at least 5 characters",
              trigger: "blur"
            }
          ],
          password: [
            { required: true, message: "Password is required", trigger: "blur" },
            {
              min: 5,
              message: "Password length should be at least 5 characters",
              trigger: "blur"
            }
          ]
        }
      };
    },
    methods: {
      simulateLogin() {
        return new Promise(resolve => {
          setTimeout(resolve, 800);
        });
      },
      getRequests() {
        var s1 = window.location.search.substring(1, window.location.search.length).split('&'),
          r = {}, s2, i;
        for (i = 0; i < s1.length; i += 1) {
          s2 = s1[i].split('=');
          r[decodeURIComponent(s2[0]).toLowerCase()] = decodeURIComponent(decodeURIComponent(s2[1]));
        }
        return r;
      },
      async login() {
        let valid = await this.$refs.form.validate();
        if (!valid) {
          return;
        }
        let formData = qs.stringify({
          username: this.model.username,
          password: this.model.password
        });
        //let formData = new FormData();
        //formData.set("username", this.model.username);
        //formData.set("password", this.model.password);
        // this.$http.post('/employee-jsons/doLogin.action', formData).then(res => {
        //       this.$message.success("Login successfull");
        //     }, err => {
        //       this.$message.error("Username or password is invalid");
        //   });

        await axios.post('/employee-jsons/doLogin.action', formData, { headers: { 'Content-Type': 'application/x-www-form-urlencoded' } })
          .then((result) => {
            //this.loginSuccessful(result);
            if (result.data.indexOf('Login failed') != -1) {
              this.$message.error("Username or password is invalid");
            } else {
              this.$message.success("Login successfull");
              this.success = true;
              //const dofuncSucc = async function () { 
              //}
              //dofuncSucc();
            }
          })
          .catch((error) => {
            //this.loginFailed();
            this.$message.error("Username or password is invalid");
          })

        if (this.success) {
          this.loading = true;
          await this.simulateLogin();
          this.loading = false;
          var QueryString = this.getRequests();
          if (QueryString["redirect"] != null && QueryString["redirect"] != "") {
            window.location.href = QueryString["redirect"];
          } else {
            window.location.href = "/";
          }
        }
        /*let valid = await this.$refs.form.validate();
        if (!valid) {
          return;
        }
        this.loading = true;
        await this.simulateLogin();
        this.loading = false;
        if (
          this.model.username === this.validCredentials.username &&
          this.model.password === this.validCredentials.password
        ) {
          this.$message.success("Login successfull");
        } else {
          this.$message.error("Username or password is invalid");
        }*/
      }
    }
  };
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
  .login {
    flex: 1;
    display: flex;
    justify-content: center;
    align-items: center;
  }

  .login-button {
    width: 100%;
    margin-top: 40px;
  }

  .login-form {
    width: 290px;
  }

  .forgot-password {
    margin-top: 10px;
  }
</style>
<style lang="scss">
  $teal: rgb(0, 124, 137);

  .el-button--primary {
    background: $teal;
    border-color: $teal;

    &:hover,
    &.active,
    &:focus {
      background: lighten($teal, 7);
      border-color: lighten($teal, 7);
    }
  }

  .login .el-input__inner:hover {
    border-color: $teal;
  }

  .login .el-input__prefix {
    background: rgb(238, 237, 234);
    left: 0;
    height: calc(100% - 2px);
    left: 1px;
    top: 1px;
    border-radius: 3px;

    .el-input__icon {
      width: 30px;
    }
  }

  .login .el-input input {
    padding-left: 35px;
  }

  .login .el-card {
    padding-top: 0;
    padding-bottom: 30px;
  }

  h2 {
    font-family: "Open Sans";
    letter-spacing: 1px;
    font-family: Roboto, sans-serif;
    padding-bottom: 20px;
  }

  a {
    color: $teal;
    text-decoration: none;

    &:hover,
    &:active,
    &:focus {
      color: lighten($teal, 7);
    }
  }

  .login .el-card {
    width: 340px;
    display: flex;
    justify-content: center;
  }
</style>