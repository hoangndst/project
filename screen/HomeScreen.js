import React, { useLayoutEffect } from 'react'
import { StyleSheet, Text, View, SafeAreaView, Button, ScrollView, TouchableOpacity } from 'react-native'
import { StatusBar } from 'expo-status-bar'
import { Avatar } from 'react-native-elements'
import CustomListItem from '../components/CustomListItem'
import { auth, db } from '../firebase'


const HomeScreen = ({ navigation }) => {

    const signOutUser = () => {
        auth.signOut().then(() => {
            navigation.replace('Login');
        });
    }

    useLayoutEffect(() => {
        navigation.setOptions({
            
            title: "Whatzup"+ " " + auth.currentUser.displayName,
            headerStyle: { backgroundColor: '#004052'},
            headerTitleStyle: { color: "#fff",},
            headerTintColor: 'white',
            headerLeft: () => (
                <View style={{ marginLeft: 17}}>
                    <TouchableOpacity onPress={signOutUser} activeOpacity={0.5}>
                    <Avatar
                        rounded
                        source={{
                            uri: auth?.currentUser?.photoURL
                        }}
                    />
                    </TouchableOpacity>
                </View> 
            ),
        });
    }, []);
    return (
        <SafeAreaView>
            <StatusBar style='light'/>
            <ScrollView>
                <CustomListItem/>
            </ScrollView>
        </SafeAreaView>
    )
}

export default HomeScreen

const styles = StyleSheet.create({})
