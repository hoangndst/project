import 'react-native-gesture-handler';
import React from 'react';
import { StatusBar } from 'expo-status-bar';
import { StyleSheet, Text, View, SafeAreaView, Image } from 'react-native';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator, HeaderTitle } from '@react-navigation/stack';
import LoginScreen from './screen/LoginScreen';
import RegisterScreen from './screen/RegisterScreen';
import HomeScreen from './screen/HomeScreen';
const Stack = createStackNavigator();

const globalScreenOptions = {
  headerStyle: { backgroundColor: "#2089DC" },
  headerTitleStyle: { color: "#fff"},
  headerTintColor: 'white',
}


export default function App() {
  return (
    <NavigationContainer>
      <Stack.Navigator
      //  initialRouteName="Home"
       screenOptions={globalScreenOptions}>
        <Stack.Screen options={{headerTitleStyle:{alignSelf: 'center'}}} name="Login" component={LoginScreen}/>
        <Stack.Screen name="Register" component={RegisterScreen} />
        <Stack.Screen name="Home" component={HomeScreen}/>
      </Stack.Navigator>
    </NavigationContainer>
  );
}

const styles = StyleSheet.create({
  container: {
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
});
